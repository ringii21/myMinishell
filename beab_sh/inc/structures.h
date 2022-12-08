/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:53:49 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/08 14:28:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H

# define STRUCTURES_H
# include "minishell.h"

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

#endif
