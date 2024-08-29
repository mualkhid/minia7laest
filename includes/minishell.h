/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:51:07 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 18:29:01 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_data
{
	t_list			*env;
}					t_data;

// typedef struct s_exit
// {
// 	int				exit_status;
// }					t_exit;

typedef struct s_cmd
{
	char			**cmd;
	char			*txt;
	char			**initials;
	struct s_cmd	*pipe;
	struct s_cmd	*next;
	struct s_cmd	*on_success;
	struct s_cmd	*on_fail;
	int				fd_out;
	int				fd_in;
	int				fd_heredocs;
	char			*cmd_path;
	int				pid;
	char			**parsing_pre_analysis;
	int				bonus;
}					t_cmd;

extern int	g_exit_status;

// HEADER
void				print_header(int fd);

// CREATE ENV
t_list				*parse_env_vars(char **env);
void				set_pwd(t_data *data);
void				shlvl(t_data *data);

// CMD
t_cmd				*get_cmd(t_data *data);
t_cmd				*init_cmd_struct(void);
t_cmd				*add_to_cmd(char *txt);
void				free_cmd(t_cmd *cmd);

// PARSING
int					chk_parenthesis(char *s);
int					chk_syntax(char *str);
int					preprocess_cmd(t_cmd **cmd, char *initial,
						t_cmd *cmd_parent, t_data *data);
int					is_logical_operator(char *txt);
int					check_if_in_special(char c, char *s);
char				**parse_redir_cmd(char *s);
char				**split_advanced(char *s, char *c);
void				parse_group(t_cmd **cmd, char *initial, t_data *data);
char				**split_string(char *s, char *c);

// ANALYSE
int					redir_in_stdin(char *filename_initial, t_cmd *cmd,
						t_data *data);
int					redir_in_heredoc(char *limiter_initial, t_cmd *cmd,
						t_cmd *cmd_parent, t_data *data);
int					redir_in_stdout(char *filename_initial, int *rd_out,
						t_data *data);
int					redir_in_append(char *filename_initial, int *rd_out,
						t_data *data);
int					parse_double_quotes(char **s, int *i, t_data *data);
int					parse_single_quotes(char **s, int *i);
int					parse_cmd(t_cmd *cmd);
char				*exec_transformation(char *original, t_data *data);
char				**do_redirections(t_cmd *cmd, t_data *data);
char				*find_filename(char *filename_initial, t_data *data);
void				replace_var(char **s, int *f, t_data *data);

// EXEC
int					check_cmds(t_cmd *cmd, t_cmd *cmd_parent, t_data *data);
int					exec_cmd(t_cmd *cmd, t_cmd *cmd_parent, t_data *data);
int					wait_cmd(t_cmd *cmd, t_cmd *cmd_parent);
char				*find_cmd_path(char **cmd, t_list *env);
void				analyse_line(t_cmd *cmd, t_data *data);

// BUILTIN
int					exec_builtin(t_cmd *cmd, t_cmd *cmd_parent, t_data *data);
int					is_in_builtin(char *cmd_name);
int					echo_cmd(t_cmd *cmd);
int					env_cmd(t_cmd *cmd, t_data *data);
int					export_cmd(t_cmd *cmd, t_data *data);
int					unset_cmd(t_cmd *cmd, t_data *data);
int					cd_cmd(char **cmd, t_data *data);
int					cmd_42(t_cmd *cmd);
int					pwd_cmd(t_cmd *cmd);
int					exit_cmd(t_cmd *cmd, t_cmd *cmd_parent, t_data *data);
char				*join_var_with_content(char *content, char *var);
void				export_null_content(t_data *data, char *var);
void				print_env_export(t_cmd *cmd, t_data *data);

void				handle_export_error(char *var);
void				add_env_var_if_missing(t_data *data, char *var);
void				print_exported_env(t_cmd *cmd, t_data *data);

// SIGNAL
void				exec_signal(void);
void				nothing_signal(void);
void				get_sig_during_cmd(void);
void				sig_during_cmd(int sig);
void				ctrl_c_heredoc(int sig);
void				before_sig_info(int mode, int fd, char *limiter);

// WILDCARDS
int					check_sequence(char *sequence, char **d_name);
int					check_first_wildards(char **s, char **d_name, t_data *data);
int					end_check(char *sequence, char *d_name);
char				**do_wildcards_word(char *s, t_data *data);

// EXIT
void				cleanup_exit(t_data *data, t_cmd *cmd_parent);

// UTILS
int					check_if_in(char c, char *s);
int					ft_cmd_len(t_list *words);
int					ft_if_file(char *str);
char				*get_pwd(void);
char				**env_vars_to_array(t_list *env);
char				*get_env_var_value(char *s, t_data *data);
void				close_fd(int fd);
char				*get_str(const char *s, size_t *i, int j);
char				**memfree(char **split, int i);

// UTILS TABS
int					aos_len(char **tab);
char				**convert_to_aos(t_list *lst);
char				*join_strings(int size, char **strs, char *sep);
void				sort_aos(char **tab, int size, int(f)(char *, char *));
void				free_aos(char **tab);

// UTILS STR
int					is_it_in_str(char *str, char c);
int					wildcards_strcmp(char *s1, char *s2);
int					export_strcmp(char *s1, char *s2);
int					only_space(char *string);
char				*strdup_unquoted(char *limiter_initial);

#endif
