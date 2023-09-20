/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:18:36 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/20 03:10:53 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <limits.h>

# define MAX_TOKEN 1000

extern int	g_status;

typedef enum e_token_type
{
	TOKEN_WORD = 0,
	TOKEN_REDIRIN,
	TOKEN_REDIROUT,
	TOKEN_REDIRAPP,
	TOKEN_HEREDOC,
	TOKEN_VAR,
	TOKEN_PIPE,
	TOKEN_EXPANDED,
	TOKEN_FILE,
	TOKEN_KEEP_Q,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	char			*str_input;
	int				i_expand;
}	t_token;

typedef struct s_command
{
	char	**cmd;
	char	*in_file;
	char	*out_file;
	char	*heredoc_delimiter;
	int		heredoc_expand;
	int		append;
	int		stdin_saved;
	int		stdout_saved;
	int		in_fd;
	int		out_fd;
}	t_command;

typedef struct s_prompt
{
	t_token				**tokens;
	struct s_command	**cmds;
	char				**env;
	int					last_pipeline_status;
	char				*wd;
	char				*old_wd;
	char				**splitted_path;
	int					pid;
	int					**pipes;
	pid_t				*childs;
	int					nb_cmd;
}	t_prompt;

// builtins.c
int			mini_echo(t_command *cmd);
int			mini_cd(t_prompt *p, t_command *cmd, char *path);
int			mini_pwd(t_prompt *p, t_command *cmd);
int			envsize(char **envp);
char		**init_mini_envp(char **envp);
int			mini_env(t_prompt *p, t_command *cmd);
char		*mini_getenv(char *name, char **envp);
void		mini_setenv(char *name, char *value, char ***envp);
void		export_no_arg(char **env);
int			mini_export(t_prompt *p, t_command *cmd);
int			mini_unset(t_prompt *p, t_command *cmd);
void		mini_unsetenv(char *name, char ***envp);
void		free_envp(char **envp);
int			mini_exit(t_prompt *p, t_command *cmd);
int			ft_atol_checker(const char *str, int *error);
int			is_neg(const char *str);
int			ft_strcmp(const char *s1, const char *s2);

// errors
void		*error_malloc_null(void);
void		error_malloc_void(void);
void		error_return(char *message);
int			error_ret(char *cmd, char *input, char *err_msg, int ret);
void		*error_null(char *cmd, int quote, char *input, char *error_msg);
void		error_msg(char *cmd, int quote, char *input, char *error_msg);
char		*join_msg(char *msg, char *to_add);
void		err_msg_heredoc(int line_nbr, t_command *cmd);
t_token		**err_msg_token(char *token_value, t_prompt *p);

// handle quotes
void		check_quotes(char *val, int *open_sq, int *open_dq, int *i);

// expander.c
void		cpy_str(char *dest, char *src, int *i, int *j);
void		replace_value(t_token *tok, char *var_val, int len, int new_len);
char		*get_var_name(char *str, int i);
int			is_expandable(char *str, int i, t_prompt *p);
int			get_i_var_toexpand(char *str, t_prompt *p, int count);
char		*get_var_toexpand(t_token *tok, char *str, t_prompt *p);
int			len_varname(char *str, int start_i);
int			is_in_value(char *var_name, char *var_value);
void		replace_var(char *start_var, int len, t_prompt *p, t_token *tok);
void		expander(t_token **toks, t_prompt *p);
int			count_quotes_after(char *str, int i);
void		handle_quotes(t_token *tok);
int			is_between_dquote(char *str, int start);
int			is_between_squote(char *str, int start);
char		*var_val_check(char *v_name, t_prompt *p, t_token *t);
int			dollar_to_delete(char *tok_value, int i);
void		del_dollar(t_token *tok);

// lexer.c
void		init_token(t_token *token);
t_token		**err_msg_token1(char *str, t_prompt *p, t_token **res, int index);
int			is_space_in_token(char *str, int i);
int			is_not_operator(char c);
void		build_quotes_token(char *str, int *index, t_token *res);
int			get_quotes_token_len(char *str, int *index);
t_token		*create_token(char *str, int *index);
t_token		*create_word_token(char *str, int *index);
t_token		*create_quotes_token(char *str, int *index);
t_token		*create_double_char_token(char *str, int *index);
t_token		*create_single_char_token(char *str, int *index);
t_token		*create_word_token(char *str, int *index);
int			word_token_len(char *str, int i);
void		word_token_squotes(char *str, t_token *res, int *index, int *i);
void		word_token_dquotes(char *str, t_token *res, int *index, int *i);
t_token		**lexer_loop(int *index, char *str, int *i, t_prompt *p);
void		build_q_token_sub1(char *str, int *index, t_token *res, int *i);
int			is_in_token(char *str, int i);
t_token		**lexer(char *str, t_prompt *p);
t_token		**finish_token(t_token **res, int *i, t_prompt *p);
t_token		**checks(int *i, t_token **res, t_prompt *p);
void		free_tokens2(t_token **res);
t_token		**err_msg_max_token(t_prompt *p, t_token **res, int index);
int			operator_in_quotes(char *str, int i);

// parser.c
int			get_cmds_nbr(t_token **tokens);
char		*parse_file_token(t_token *token);
char		*parse_delim_heredoc(t_token *token, t_command *res);
int			is_valid_filename(t_token *token);
void		init_cmd(t_command *cmd);
int			get_cmd_len(t_token **tokens, int i);
t_command	*is_redir(t_prompt *p, int *index, int j, t_command *res);
int			is_redir_redirin(int *index, t_prompt *p, t_command *res, int j);
int			is_redir_redirapp(int *index, t_prompt *p, t_command *res, int j);
int			is_redir_redirout(int *index, t_prompt *p, t_command *res, int j);
t_command	*create_cmd(t_prompt *p, int *index);
t_command	*is_heredoc(t_prompt *p, int *index, int j, t_command *res);
t_command	**parser(t_prompt *p);
void		is_heredoc_sub1(t_command *res, t_prompt *p, int *index);
void		part1(t_prompt *p, int *index, t_command *res);
t_command	*part2(t_prompt *p, int *i, t_command *res);
void		split_token(t_token *tok, char *str, int *j, t_command *res);
void		copy_into_filename(char *filename, char *value);

// pipeline.c
void		append_backslash(char **splitted_path);
int			get_cmds_nbr2(t_command **cmds);
void		exec_cmd(t_prompt *p, int i);
void		save_fds(t_command *cmd);
void		setup_fd(int **pipes, int i, int n);
void		init_pipes(int **pipes, int n);
void		start_pipeline(int **pipes, pid_t *childs, t_prompt *p);
void		stop_pipeline(int **pipes, pid_t *childs, int n, t_prompt *p);
void		pipeline(t_prompt *p);
void		ft_strcpy(char *dst, const char *src);
int			is_dir(t_prompt *p, char *str);
void		check_cmd_not_found(char *path);
pid_t		*create_childs(int num_commands);
int			**create_pipes(int num_commands);
void		free_pipes_and_childs(t_prompt *p);
int			has_invalid_cmd(t_command **cmds);
void		start_pipeline_sub1(int n, t_prompt *p, int **pipes, int *childs);
void		check_path(t_prompt *p, char **cmd);

// executor.c
void		parse_args(t_prompt *p, char *input);
int			quotes_checker(char *str);
void		free_all2(t_prompt *p);
int			parse_args_sub1(char *input, t_prompt *p);

// minishell.c
int			valid_file_redir(t_command *cmd);
void		clean_old_file(t_command *cmd, int in_file);
void		clean_old_heredoc(t_command *cmd);
void		setup_redir(t_command *cmd, t_prompt *p);

void		reset_fds(t_command *cmd);
void		close_fds(t_command *cmd, int out_fd);

int			redir_out(t_command *cmd, int append, t_prompt *p);
int			redir_in(t_command *cmd, t_prompt *p);
int			write_in_heredoc(t_command *cmd, t_prompt *p);
char		*expand_heredoc(char *line, t_prompt *p);
int			get_i_var(char *str);
int			len_var(char *str);
int			heredoc(t_command *cmd, t_prompt *p);
int			is_builtin(char *str);
int			exec_builtins(t_prompt *p, t_command *cmd);

// signal.c
void		sigint_handler(int sig);

// free.c
void		free_command(t_command *cmd);
void		free_commands(t_prompt *p);
void		free_tokens(t_prompt *p);
void		free_environment(t_prompt *p);
void		free_splitted_path(t_prompt *p);
void		free_prompt(t_prompt *p);

// heredoc
void		write_in_heredocsub1(char *exp_line, char *line,
				t_command *cmd, int *line_nbr);
void		end_line(char *line, int fd);

//env
void		increment_shlvl(t_prompt *p);

//expander.c
void		expander_sub1(t_token **t);

#endif
