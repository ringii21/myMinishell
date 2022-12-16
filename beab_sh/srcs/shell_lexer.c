/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 22:27:20 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/16 22:32:21 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*lexer(t_main *m)
{
	char	*tmp;

	m->p = init_parser();
	tmp = NULL;
	tmp = ft_strtrim(m->line, " \f\t\n\r\v");
	if (!tmp)
		return (NULL);
	if (!ft_check_if_not_valid_pipes(tmp, -1, true)
		|| !ft_check_if_not_valid_redir(tmp, -1, true)
		|| !check_quotes_is_valid(tmp))
		free(tmp);
	return (tmp);
}
