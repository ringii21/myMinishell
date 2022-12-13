/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:53:49 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/13 12:28:02 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H

# define STRUCTURES_H
# include "minishell.h"

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::ENVIRONMENT::

typedef struct s_env
{
	char			*var;
	char			*cont;
	char			*total;
	int				stat_code;
	struct s_env	*next;
}	t_env;

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::PARSING::

typedef enum e_type
{
	DEFAULT,
	REDIR_IN,
	REDIR_OUT,
	R_REDIR_IN,
	R_REDIR_OUT,
}	t_type;

typedef struct s_redir
{
	char				*path;
	char				*filename;
	enum e_type			type;
	int					fd;
	int					fd_pipe[2];
	struct s_redir		*next;
	bool				is_quote;
}	t_redir;

typedef struct s_token
{	
	pid_t			pid;
	int				cmd_ac;
	bool			is_pipe;
	int				is_pipe_open;
	int				pipe_fd[2];
	char			**cmds_av;
	char			*av_copy;
	char			*path;
	t_redir			*file;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_parse
{
	int				i;
	char			*read;
	char			*var;
	t_token			*list;
	t_token			*cursor;
	enum e_type		type;
	bool			is_quote;
}	t_parse;

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::MAIN::

typedef struct s_main
{
	char			*cwd;
	char			*prompt;
	char			*line;
	t_token			*t;
	t_env			*env;
}	t_main;

#endif
