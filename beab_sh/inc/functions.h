/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:26:51 by root              #+#    #+#             */
/*   Updated: 2022/12/08 14:28:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H

# define FUNCITONS_H
# include "minishell.h"

int		set_signals(void);
t_env	*put_env(char **envp);
char	*get_cont(char *name_var, t_env *env);
t_env	*ft_if_env_empty(void);
t_env	*fill_env(char *is_env);
t_obj	*ft_parcing(t_main *m);
void	ft_flush(t_obj *o);
int		job(t_main *m);
int		is_builtin(char **cmds);
int		ft_input(t_obj *o, t_env *env);
int		ft_output(t_obj *o);
int		ft_child_play(t_obj *o, t_env *env, bool builtin);
void	ft_close_pipe(t_obj *o);
int		ft_cd(t_obj *o, t_env *env, bool is_forked);
int		ft_echo(t_obj *o);
int		ft_export(t_obj *o, t_env *env, bool is_forked);
int		ft_env(t_env *env);
int		ft_pwd(t_env *env);
int		ft_exit(t_obj *o, bool is_forked);
int		ft_unset(t_obj *o, t_env *env, bool is_forked);
int		ft_create_o_replace(char *namevar, char *value, t_env *env);
int		ft_check_and_export(char *namevar, char *value, t_env *env, bool is_forked);
void	ft_print_declare(t_env *env, bool is_forked);
int		ft_add_env(char *namevar, char *value, t_env *env);
char	**ft_env_to_tab(t_env *env);
int		exec_builtin(t_obj *o, t_env *env, bool is_forked);
int		shut_signals(int fork);
int		set_signals(void);

#endif