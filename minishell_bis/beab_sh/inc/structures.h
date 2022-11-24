/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wac <wac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:53:49 by seozcan           #+#    #+#             */
/*   Updated: 2022/11/17 14:33:18 by wac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H

# define STRUCTURES_H
# include "minishell.h"
#include <stdbool.h>

enum	redir_type
{
	NONE,
	REDIR_IN,
	REDIR_OUT,
	R_REDIR_IN, 
	R_REDIR_OUT,
};

typedef struct s_list_f
{
	char				*path;
	enum				redir_type	type;
	int					fd;
	int	 				fd_pipe[2];
	struct s_list_f		*next;
	bool				is_quote;
}				t_list_f;

typedef struct s_env
{
	char			*var;
	char			*cont;
	char			*total;
	int				stat_code;
	struct s_env	*next;
}	t_env;

typedef struct s_obj
{	
	pid_t	pid;
	bool		is_pipe;
	int		is_pipe_o;
	int		cmd_ac;
	int		pipe_fd[2];
	char	**cmds_av;
	char	*av_copy;
	char 	*path;
	t_list_f	*file;
	struct s_obj	*next;
	struct s_obj	*prev;
	
}	t_obj;

typedef struct s_parcing
{
	int				i;
	char			*read;
	char			*var;
	t_obj			*list;
	t_obj			*ici;
	enum redir_type	type;
	bool			is_quote;
}				t_parcing;

typedef struct s_main
{
	char			*cwd;
	char			*prompt;
	char			*line;
	t_obj			*o;
	t_env			*env;
}	t_main;

int set_signals(void);
t_env *put_env(char **envp);
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
 int	exec_builtin(t_obj *o, t_env *env, bool is_forked);
int		shut_signals(int fork);
int		set_signals(void);
#endif
