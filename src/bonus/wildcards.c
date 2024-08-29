/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:54:22 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/20 18:54:24 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_if_wildcard(char *s, char *dir_name, t_data *data)
{
	int		i;
	int		quote;
	int		d;
	char	*sub;

	i = 0;
	d = 0;
	quote = 0;
	while (s[i])
	{
		if (s[i] == '*' && !quote)
		{
			sub = exec_transformation(ft_substr(s, d, i - d), data);
			if (!check_sequence(sub, &dir_name))
				return (0);
			d = i + 1;
		}
		else if (s[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	sub = exec_transformation(ft_substr(s, d, i - d), data);
	return (end_check(sub, dir_name));
}

static void	check_word_match(char *dir_name, char *s, t_list **wild,
		t_data *data)
{
	char	*temp;

	if (ft_memcmp(dir_name, ".", 1))
	{
		temp = dir_name;
		if (check_first_wildards(&s, &dir_name, data))
		{
			if (check_if_wildcard(s, dir_name, data))
				ft_lstadd_back(wild, ft_lstnew(ft_strdup(temp)));
		}
	}
}

static void	get_cd(char *s, t_list **words, t_data *data)
{
	DIR				*dp;
	char			*pwd;
	int				read_next;
	struct dirent	*dirp;

	pwd = get_pwd();
	if (pwd == NULL)
		return ;
	dp = opendir(pwd);
	free(pwd);
	if (dp == NULL)
		return (perror("opendir"));
	read_next = 1;
	while (read_next)
	{
		dirp = readdir(dp);
		if (dirp == NULL)
			read_next = 0;
		else
			check_word_match(dirp->d_name, s, words, data);
	}
	if (closedir(dp))
		perror("closedir");
}

static char	**ft_sort_str(t_list *words)
{
	char	**split;
	int		size;

	split = convert_to_aos(words);
	ft_lstclear(&words, &free);
	if (split == NULL)
		return (0);
	size = 0;
	while (split[size])
		size++;
	sort_aos(split, size, wildcards_strcmp);
	return (split);
}

char	**do_wildcards_word(char *s, t_data *data)
{
	t_list	*words;
	char	*cpy;

	words = 0;
	cpy = ft_strdup(s);
	if (!cpy)
		return (NULL);
	get_cd(cpy, &words, data);
	free(cpy);
	return (ft_sort_str(words));
}
