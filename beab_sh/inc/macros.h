/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:55:19 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/15 17:56:41 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H

# define MACROS_H

# include "minishell.h"

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::OUTPUTS::

//			names
# define MINI_MSG	"minishell: "
# define HERE_DOC	"/.heredoc_tmp"

//			exec error messages
# define ERR		"error: "
# define ERR_ARGS	": no arguments allowed.\n"
# define ERR_FORK	": failed to fork processus.\n"
# define ERR_FILE	": no such file or directory.\n"
# define ERR_PERM	": permission denied.\n"
# define ERR_CMD	": command not found\n"

//			parsing error messages
# define ERR_PIPE	"minishell: syntax error near unexpected token `|`\n"
# define ERR_NL		"minishell: syntax error near unexpected token `newline'\n"
# define ERR_QUOTE	"minishell: unclosed quote detected\n"

//			exit
# define EXIT_MSG	"exit\n"

//			operators
# define DOUBLE_Q	34
# define AMPERSAND	38
# define SINGLE_Q	39
# define OPEN_P		40
# define CLOSED_P	41
# define LEFT_A		60
# define RIGHT_A	62
# define PIPE		124

#endif