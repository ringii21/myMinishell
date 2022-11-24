/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:53:49 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/12 14:10:38 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H

# define STRUCTURES_H

# include "minishell.h"

typedef enum e_types
{
	WORD,
	OPERATOR,
	O_SPACE,
}	t_types;

typedef enum e_states
{
	DEFAULT,
	OPEN_QUOTE,
	CLOSE_QUOTE,
}	t_states;

typedef struct s_node
{
	unsigned int	type;
	char			*arg;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*head;
	t_node	*tail;
}	t_stack;

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
	int		index;
	int		fd_in;
	int		fd_out;
	int		pipe_nb;
	int		cmd_nb;
	int		cmd_ac;
	int		*fd_pipe;
	char	*infile;
	char	*outfile;
	char	*bin_path;
	char	**cmds;
	char	**cmd_flags;
	char	**paths;
	char	**envtab;
}	t_obj;

typedef struct s_main
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	type;
	int				err;
	int				ret;
	int				exit;
	int				state;
	char			quote;
	char			c;
	char			*line;
	char			*cwd;
	char			*prompt;
	char			*buff;
	t_obj			o;
	t_env			*env;
	t_stack			*lexicon;
	t_stack			*tokens;
}	t_main;

/*******************************************************************/
//					possible structure

enum e_redir_type
{
	NOPE,
	INPUT,
	OUTPUT,
	D_INPUT,
	D_OUTPUT
};

typedef struct s_redir
{
	int				pipe[2];
	int				fd;
	enum e_redir_type	type;
	char			*path;
	struct s_redir	*next;
	struct s_redir	*prev;	
}				t_redir;

typedef struct s_cmd
{
	char			**av;
	char			*path;
	bool			is_piped;
	int				ac;
	int				pipes[2];
	pid_t			pid;
	t_redir			*list;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_mainbis
{
	t_cmd		*cmds;
	t_env		*env;
	//t_parser	*whatever;
}				t_mainbis;

#endif
