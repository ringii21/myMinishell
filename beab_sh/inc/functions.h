/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:26:51 by root              #+#    #+#             */
/*   Updated: 2022/12/17 01:10:53 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H

# define FUNCTIONS_H
# include "minishell.h"

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::INIT::

//		shell_sig_set.c
int		set_signals(void);
int		set_sig(void);

//		shell_signals.c
int		shut_signals(int fork);
void	ft_cntlc(int sig);
void	ft_cntl_slsh(int sig);

//		shell_env.c
int		ft_create_o_replace(char *namevar, char *value, t_env *env);
int		ft_add_env(char *namevar, char *value, t_env *env);
t_env	*put_env(char **envp);
void	free_env(t_env *env);

//		utils_env.c
char	*get_cont(char *name_var, t_env *env);
t_env	*ft_if_env_empty(void);
t_env	*fill_env(char *is_env);
char	**ft_env_to_tab(t_env *env);

//		shell_lvl.c
void	shlvl_up(t_main *m);

//		shell_init.c
t_parse	*init_parser(void);
t_token	*init_token(void);

//		shell_flush.c
void	free_tokens(t_token *t);
void	free_parser(t_parse *p);
void	ft_flush(t_token *t);

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::PARSING::

//		shell_parsing.c
t_token	*parser(t_main *m);

//		shell_parsing_utils.c
void	count_ac(t_token *t);
void	next_token(t_token **cursor, int is_pipe);

//		shell_lexer.c
char	*lexer(t_main *m);
int		ft_check_if_not_valid_redir(char *line, int i, bool err, size_t len);
int		ft_check_if_not_valid_pipes(char *line, int i, bool err, size_t len);

//		utils_quotes.c
int		check_empty_quotes(t_main *m, char *tmp);
int		check_quotes_is_valid(t_main *m, char *line);
void	check_quotes(char c, int *b_quote, int *quotes);

//		shell_redir.c
int		redir_manager(t_main *m, t_parse *p, char *str);
int		expand_var(t_env *env, char **token, int *i, char *str);
char	*pull_varname(char *str, int *cursor);
void	var_lector(t_token *cursor, char *var, char **reading, t_env *env);
char	*pull_varvalue(char *varname, t_env *env, int *is_free);

//		shell_expansion.c
char	*make_token(char *str, int *cursor, char c, t_env *env);

//		shell_structures.c
void	fill_args(char **str, t_type *type, t_token *t, bool *is_quote);
void	fill_redir(t_token *t, char *str, t_type type, bool *is_quote);

//		utils.c
void	split_args(t_token *t, char *str);
char	*ft_strdupcat(char *s, char *t, int len);
int		ft_strcmplen(char *s1, char *s2);

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::EXECUTION::

//		shell_jobs.c
int		job(t_main *m);
int		exec_builtin(t_token *t, t_env *env, bool is_forked);

//		shell_path.c
int		which_path(t_main *m, t_token *t);

//		shell_io.c
int		ft_redir(t_token *t, t_env *env);
void	ft_close_fd(t_token *t);

//		heredoc.c
int		heredoc(t_token *t, t_redir *r, t_env *env);
int		ft_heredoc_loop(t_token *t, t_env *env, t_redir *r, int fd);

//		shell_signals_heredoc.c
void	set_signal_heredoc(void (*sig_handler)(int), int sig);
void	interrupt_heredoc(int sig);
void	ignore_sig(int sig);

//		shell_pipes.c
int		child_process(t_token *t, t_env *env);
void	close_pipes(t_token *t);

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::BUILTINS::

//		shell_cd.c
int		ft_cd(t_token *t, t_env *env, bool is_forked);
char	*ft_path_finder(t_token *t, t_env *env, bool is_forked);

//		shell_echo.c
int		ft_echo(t_token *t);

//		shell_export.c
int		ft_export(t_token *t, t_env *env, bool is_forked);

//		shell_builtins.c
int		ft_env(t_env *env);
int		ft_pwd(t_env *env);
int		is_builtin(char **cmds);
int		exec_builtin(t_token *t, t_env *env, bool is_forked);

//		shell_exit.c
int		ft_exit(t_token *t, bool is_forked, t_env *env);
int		ft_mini_exit(int status, t_token *t, t_env *env);

//		shell_unset.c
int		ft_unset(t_token *t, t_env *env, bool is_forked);
int		ft_exec_unset(char *namevar, t_env *env);

//		utils_builtins.c

//		utils_export.c
int		ft_check_and_export(char *namevar, char *value, t_env *env,
			bool is_forked);
void	ft_print_declare(t_env *env, bool is_forked);

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::DEBUG::

//		shell_err_msg.c
int		return_error_cmd_nf(t_token *t);
int		return_error_no_file(t_redir *file);
int		return_error_access_denied(t_redir *file);
int		ft_error_msg(int ret, char *err_msg);

//		shell_printlist.c
void	print_tokens(t_token *t);
void	print_redir(t_redir *r);

#endif
