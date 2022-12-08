/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:53:49 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/08 14:37:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H

# define STRUCTURES_H
# include "minishell.h"

enum	redir_type
{
	DEFAULT,
	REDIR_IN,
	REDIR_OUT,
	R_REDIR_IN, 
	R_REDIR_OUT,
};

typedef struct s_redir
{
	char				*path;
	enum				redir_type	type;
	int					fd;
	int	 				fd_pipe[2];
	struct s_redir		*next;
	bool				is_quote;
}	t_redir;

typedef struct s_env
{
	char			*var;
	char			*cont;
	char			*total;
	int				stat_code;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{	
	pid_t			pid;
	bool			is_pipe;
	int				is_pipe_o;
	int				cmd_ac;
	int				pipe_fd[2];
	char			**cmds_av;
	char			*av_copy;
	char 			*path;
	t_redir			*file;
	struct s_token	*next;
	struct s_token	*prev;
	
}	t_token;

typedef struct s_parsing
{
	int				i;
	char			*read;
	char			*var;
	t_token			*list;
	t_token			*ici;
	enum redir_type	type;
	bool			is_quote;
}	t_parsing;

typedef struct s_main
{
	char			*cwd;
	char			*prompt;
	char			*line;
	t_token			*o;
	t_env			*env;
}	t_main;

#endif
