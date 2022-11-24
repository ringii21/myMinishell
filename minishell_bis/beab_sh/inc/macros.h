/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:55:19 by seozcan           #+#    #+#             */
/*   Updated: 2022/09/27 18:33:11 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H

# define MACROS_H

# include "minishell.h"

//			minishell
# define ERR			"Error:"
# define ERR_ARGS		"usage: ./minishell [NO ARGS]"
# define ERR_ENV		"Empty environnement:"
# define ERR_VAR		"Variable not found:"
# define ERR_PIPE		"Pipe failed:"
# define ERR_CMD		"Command not found:"
# define ERR_EXEC		"Execution failed:"
# define ERR_MALLOC		"Memory allocation has failed:"

//			operators
# define DOUBLE_Q		34
# define AMPERSAND		38
# define SINGLE_Q		39
# define OPEN_P			40
# define CLOSED_P		41
# define LEFT_A			60
# define RIGHT_A		62
# define PIPE			124

#endif