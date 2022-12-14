/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:26:51 by root              #+#    #+#             */
/*   Updated: 2022/12/14 22:59:03 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H

# define FUNCTIONS_H
# include "minishell.h"

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::INIT::
//		shell_signals.c
int		set_signals(void);
int		shut_signals(int fork);
int		set_signals(void);
int		set_sig(void);
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
t_parse	init_parser(void);
t_token	*init_token(void);

//		shell_flush.c
void	ft_flush(t_token *t);

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::PARSING::
//		shell_parsing.c
t_token	*parser(t_main *m);

//		shell_parsing_utils.c
int		ft_check_if_not_valid_redir(char *line, int i, bool err);
int		ft_check_if_not_valid_pipes(char *line, int i, bool err);


//		shell_redir.c
int		redir_manager(t_parse *p, char *str);
int		expand_var(t_env *env, char **token, int *i, char *str);
char	*pull_varname(char *str, int *cursor);
void	var_lector(t_token *cursor, char *var, char **reading, t_env *env);
char	*pull_varvalue(char *varname, t_env *env);

//		shell_expansion.c
char	*make_token(char *str, int *cursor, char c, t_env *env);

//		shell_structures.c
void	fill_args(char **str, t_type *type, t_token *t,
			bool *is_quote);
void	fill_redir(t_token *t, char *str, t_type type,
			bool *is_quote);

//		utils.c
void	split_args(t_token *t, char *str);
char	*ft_strdupcat(char *s, char *t, int len);
int		ft_strcmplen(char *s1, char *s2);
void	ft_error_msg(char *err_msg);

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
int		heredoc(t_token *t, t_env *env);

//		shell_signals_heredoc.c
void	set_signal_heredoc(void (*sig_handler)(int), int sig);
int		ft_heredoc_loop(t_token *t, int fd);
void	interrupt_heredoc(int sig);
void	ignore_sig(int sig);


//		shell_pipes.c
int		child_process(t_token *t, t_env *env, bool builtin);
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
int		ft_exit(t_token *t, bool is_forked);

//		shell_unset.c
int		ft_unset(t_token *t, t_env *env, bool is_forked);
int		ft_exec_unset(char *namevar, t_env *env);

//		utils_builtins.c


//		utils_export.c
int		ft_check_and_export(char *namevar, char *value, t_env *env,
			bool is_forked);
void	ft_print_declare(t_env *env, bool is_forked);

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::DEBUG::
//		shell_printlist.c
void	print_tokens(t_token *t);
void	print_redir(t_redir *r);

#endif
