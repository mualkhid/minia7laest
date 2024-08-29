/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:55:21 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 18:26:04 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_filename(char *filename_initial, t_data *data)
{
	char	**wildcards;
	char	*filename;

	if (check_if_in_special('*', filename_initial))
	{
		wildcards = do_wildcards_word(filename_initial, data);
		if (!wildcards || aos_len(wildcards) > 1)
			filename = NULL;
		else if (wildcards[0] == 0)
			filename = exec_transformation(ft_strdup(filename_initial), data);
		else
			filename = ft_strdup(wildcards[0]);
		free_aos(wildcards);
	}
	else
		filename = exec_transformation(ft_strdup(filename_initial), data);
	return (filename);
}

int	redir_in_stdout(char *filename_initial, int *rd_out, t_data *data)
{
	char	*filename;

	close_fd(*rd_out);
	filename = find_filename(filename_initial, data);
	if (filename)
	{
		*rd_out = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (*rd_out == -1)
			perror("open");
	}
	else
	{
		free(filename);
		g_exit_status = 1;
		ft_putstr_fd("wrong redirect\n", 2);
		*rd_out = -1;
		return (0);
	}
	free(filename);
	return (1);
}

int	redir_in_append(char *filename_initial, int *rd_out, t_data *data)
{
	char	*filename;

	close_fd(*rd_out);
	filename = find_filename(filename_initial, data);
	if (filename)
	{
		*rd_out = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (*rd_out == -1)
			perror("open");
	}
	else
	{
		free(filename);
		g_exit_status = 1;
		ft_putstr_fd("ambiguous redirect\n", 2);
		*rd_out = -1;
		return (0);
	}
	free(filename);
	return (1);
}
