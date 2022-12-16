/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:53:49 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/16 23:54:15 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H

# define STRUCTURES_H
# include "minishell.h"

extern int	g_status;

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
	char				*file_path;
	char				*file_name;
	enum e_type			type;
	int					fd;
	struct s_redir		*next;
	bool				is_quote;
	int					nb_heredoc;
}	t_redir;

typedef struct s_token
{	
	pid_t			pid;
	size_t			cmd_ac;
	bool			is_pipe;
	bool			is_error;
	bool			is_parent;
	bool			is_builtin;
	int				is_pipe_open;
	int				pipe_fd[2];
	char			**cmds_av;
	char			*bin_path;
	t_redir			*file;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_parse
{
	int				i;
	char			*read;
	char			*var;
	enum e_type		type;
	bool			is_quote;
}	t_parse;

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::MAIN::

typedef struct s_main
{
	char			*cwd;
	char			*prompt;
	char			*line;
	int				u;
	t_parse			*p;	
	t_token			*cursor;
	t_token			*t;
	t_env			*env;
}	t_main;

#endif
