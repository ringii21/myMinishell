/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:53:49 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/29 23:24:35 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H

# define STRUCTURES_H

# include "minishell.h"

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::LEXER::

typedef enum e_types
{
	T_WORD,
	T_OPERATOR,
	T_SPACE,
	T_QUOTE,
}	t_types;

typedef enum e_states
{
	S_DEFAULT,
	S_OPEN_QUOTE,
	S_CLOSING_QUOTE,
}	t_states;

typedef struct s_lexer
{	
	char			arg;
	enum e_types	type;
}	t_lexer;

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::PARSING::

typedef enum e_operator
{
	O_PIPE,
	O_OR,
	O_AND,
	O_STDIN_REDIR,
	O_STDOUT_REDIR,
	O_DELEM,
	O_APPEN,
	O_CMD,
}	t_operator;

typedef struct s_token
{
	enum e_operator	id;
	char			**av;
	char			*bin_path;
	char			*file_path;
	pid_t			pid;
	int				pipe[2];
	int				fd;
	bool			is_piped;
	bool			is_redir;
}	t_token;

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::ENVIRONMENT::

typedef struct s_env
{
	char			*var;
	char			*cont;
	char			*total;
	int				stat_code;
	struct s_env	*next;
}	t_env;

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::MAIN::

typedef struct s_main
{
	size_t			i;
	size_t			j;
	size_t			k;
	size_t			index;
	size_t			pipe_ac;
	size_t			cmd_ac;
	enum e_states	state;
	enum e_types	type;
	int				exit;
	int				*pipes;
	char			quote;
	char			*line;
	char			*cwd;
	char			*prompt;
	char			*buf;
	char			**stab;
	char			**paths;
	char			**builtins;
	char			**operators;
	t_env			*env;
	t_node			*lexicon;
	t_node			*tokens;
	t_node			*tmp;
}	t_main;

#endif
