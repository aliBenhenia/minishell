/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:40:37 by abenheni          #+#    #+#             */
/*   Updated: 2023/05/16 15:05:52 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SPACE 0
# define APPEND 1
# define HEREDOC 2
# define RIGHTRED 3
# define LEFTRED 4
# define DOLLAR 5
# define PIPE 6
# define S_QUOTE 7
# define D_QUOTE 8
# define WORD 9
# define AFDOLLAR 10
# define NLINE 11

typedef struct line
{
	char		*value;
	int			type;
	struct line	*next;
	struct line	*prev;
}t_token_list;

typedef struct redirections
{
	int					type;
	char				*file;
	int					fd;
	struct redirections	*next;
}t_redirections;

typedef enum sep
{
	e_nline,
	e_pipe,
}t_sep;

typedef struct cmd_line
{
	char			**str;
	t_redirections	*redirections;
	t_sep			separator;
	struct cmd_line	*next;
}t_cmd_line;

typedef struct env_list
{
	char			*name;
	char			*value;
	int				flag;
	struct env_list	*next;
}t_env_list;

typedef struct t_export
{
	char			*var;
	char			*value;
	int				flag;
	struct t_export	*next;
}t_export;

typedef struct tools
{
	int				i;
	int				j;
	int				k;
	int				l;
	char			*new;
	int				flag;
	int				there_is_dollar;
	int				s_quote;
	int				d_quote;
	int				no_expand;
	int				dollar_in;
	char			**str;
	t_redirections	*redirections;
	char			*tmp;
}t_tools;

typedef struct exec_tools
{
	t_cmd_line		*cmd_tmp;
	t_redirections	*l_infile;
	t_redirections	*l_outfile;
	pid_t			*pid;
	int				i;
	int				flg;
	int				fd_heredoc;
}t_exec_tools;

typedef struct allocated
{
	void				*allocated;
	struct allocated	*next;
}t_allocated;

typedef struct global
{
	int				exit_state;
	int				heredoc;
	int				i;
	int				lastchance;
	t_allocated		*allocated;
}t_global;

extern t_global	g_var;

void			rl_replace_line(const char *str, int i);
t_token_list	*tokenizer(char *line, t_token_list *tokens, t_tools *tools);
char			*is_redirections(t_token_list **tokens,
					char *line, t_tools *tools);
char			*is_wspace(t_token_list **tokens, char *line);
char			*is_dollar_pipe(t_token_list **tokens, char *line);
char			*is_word(t_token_list **tokens, char *line);
char			*is_squote(t_token_list **tokens, char *line, t_tools *tools);
char			*is_dquote(t_token_list **tokens, char *line, t_tools *tools);
char			*afdollar(t_token_list **tokens, char *line);
char			*is_space(t_token_list **tokens, char *line);
char			*ft_dquotes(t_token_list **tokens, char *line, t_tools *tools);
char			*no_expand(t_token_list **tokens, char	*line, t_tools *tools);
void			open_quote_error(t_token_list **tokens);
void			expand(t_token_list **tokens, t_env_list **env);
t_env_list		*add_var(char *name, char *value);
void			fill_env_list(t_env_list **env_list, t_env_list *new);
void			env_vars_list(t_env_list **env_list, char **env);
int				syntax(t_token_list *tokens);
void			*parser(t_cmd_line **cmd_line, t_token_list *tokens);
void			parser_word(t_token_list **tokens, char ***str,
					char **tmp, int *i);
void			parser_redirections(t_token_list **tokens,
					t_redirections **redirections);
void			parser_space(t_token_list **tokens, char **tmp, int *i);
void			parser_cmd_line(t_cmd_line **cmd_line, t_token_list **tokens,
					char **str, t_redirections *redirections);
t_redirections	*init_redirection(int type, char *file);
void			fill_redirections_list(t_redirections **redirections,
					t_redirections *new);
void			separator(t_cmd_line *cmd, t_token_list *token);
t_cmd_line		*init_cmdline(char **str, t_redirections *redirections,
					t_token_list *token);
void			fill_cmd_line(t_cmd_line **cmdline, t_cmd_line *new);
int				to_alloc_count(t_token_list **tokens);
void			execution(t_cmd_line **cmd_line, t_env_list **env_list,
					t_export **export_list);
int				main_builtins(t_cmd_line **cmd_line);
void			execute_builtins(t_cmd_line **cmd_line,
					t_env_list **env_list,
					t_export **export_list);
int				builtins(char	*cmd);
void			exec_builtins(char	**str, t_env_list **env_list,
					int code, t_export **export);
char			*get_home_var(t_env_list **env_list);
char			**get_path(t_env_list **env_list);
int				count_list(t_cmd_line **cmd_line);
int				count_envlist(t_env_list **env_list);
char			**create_envp(t_env_list **env_list);
int				last_in_out(t_cmd_line **cmd_line, t_redirections **last_in,
					t_redirections **last_out, int flag);
int				last_infile(t_cmd_line **cmd_line, t_redirections **last_in,
					t_redirections **tmp);
int				last_outfile(t_cmd_line **cmd_line, t_redirections **last_out,
					t_redirections **tmp);
void			dup_to_pipe(int **fd, int i, int cmds);
void			dup_outfile(t_redirections *redirection);
void			dup_infile(t_redirections *redirection, int fd_heredoc);
void			close_pipes(int **fd, int *i, int cmds, int flag);
int				ft_heredoc(t_cmd_line **cmd_line);
void			execute_command_2(t_cmd_line **cmd_line, t_env_list **env_list,
					t_export **export);
void			execve_func(char **cmd, t_env_list **env_list);
char			*check_command_in_path(char **path, char *cmd);
void			ft_cd(char *path, t_env_list **env_list, int flag);
void			ft_pwd(int flag);
void			ft_echo(char **str, int flag);
void			do_unset(char *str[], t_export **data,
					t_env_list **env_list, int flag);
void			do_export(char *str[], t_export **data,
					t_env_list **env_list, int flag);
void			init_env(t_export **export, t_env_list **env_list,
					char **env);
void			do_exit(char **s, int flag);
void			print_error(char *cmd, char *error, int exit_status, int flag);
void			ft_putstr(char	*str);
void			free_2d(char **str);
int				ft_isalnum(int c);
int				is_open_quote(char *line, char quote);
int				ft_strcmp(char *s1, char *s2);
int				ft_strncmp(const char *str1, const char *str2, size_t n);
int				ft_strlen(char *str);
int				count(char *line);
int				all_spaces(char *line, int i);
char			*remove_additional_spaces(char *line);
char			*ft_strchr(char *str, int c);
void			ft_lstclear(t_token_list	**lst);
void			addback(t_token_list **tokens, char *value, int type);
char			*ft_strjoin(char *s1, char *s2);
char			**ft_split(char const *s, char c);
t_token_list	*new_token(char *value, int type);
char			*ft_itoa(int n);
char			*ft_itoa_free(int n);
char			*ft_strdup(char *src);
char			*ft_strndup(char *src, int len);
char			*ft_strndup2(char *src, int len);
char			*ft_strdup_export(char *src);
void			addback_env2(t_env_list **a, t_env_list *new);
t_export		*addnew_export(char *var, char *value);
void			addback_export(t_export **a, t_export *new);
t_env_list		*addnew_env(char *var, char *value);
void			addback_env(t_env_list **a, t_env_list *new);
void			do_env(char *env[]);
int				check_if_equal_is(char *str);
int				check_if_exist(char *name, t_export *export);
char			*get_name(char *s);
char			*get_value(char *s);
void			edit_value(char *name, char *value, t_export **data,
					t_env_list **env_list);
int				check_append(char *s);
void			append_string(char *name, char *value, t_export **export,
					t_env_list **env_list);
void			error_od_export(char *s);
int				correct_name(char *s);
int				eqaul_last_only(char *s);
void			edit_env(t_env_list	**env_list, char *name, char *value);
void			append_env(t_env_list **env_list, char *name, char *value);
void			insert(t_export **head, t_export *new_node);
void			sort(t_export **head);
void			ft_putstr_fd(char *s, int fd);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
void			*ft_malloc(int size, int count);
char			**split_env_var(char *env);
char			*ft_strjoin_heredoc(char *s1, char *s2);
char			*ft_strjoin_export(char *s1, char *s2);
void			ft_shlvl(t_env_list **envlist, t_export **export);
void			exit_error(char *arg, char *error, int exit_status);
void			custom_edit_env(t_env_list	**env_list,
					char *name, char *value);
void			custom_edit_value(char *name, char *value, t_export **data,
					t_env_list**env_list);
void			free_rows(char **str);
void			free_unset_env(t_env_list *temp);
void			free_unset_export(t_export *temp);
void			edit_free(char **name_value, t_export **export,
					t_env_list **env_list);
void			append_free(char **name_value, t_export **export,
					t_env_list **env_list);
void			addback_free(t_export **export,
					t_env_list **env_list, char **name_value);
int				correct_name_unset(char *s);
void			exit_error(char *arg, char *error, int exit_status);
void			free_all(void);
void			ctrlc(int sig);
void			open_quote_error(t_token_list **tokens);
char			**fill_name_value(char *str);

#endif
