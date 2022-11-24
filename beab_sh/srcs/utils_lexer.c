/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:24:16 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/08 16:21:05 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_operator(char c, t_main *m)
{	
	if ((!ft_isprint(c) || c == ' ') && m->state == DEFAULT)
		return (O_SPACE);
	if ((c == '$' && m->quote == DOUBLE_Q && m->state == OPEN_QUOTE)
		|| (ft_strchr("|&()><*?[]$\'\"#", c) && m->state == DEFAULT))
		return (OPERATOR);
	return (WORD);
}

int	is_quote(char c, t_main *m)
{
	if ((c == DOUBLE_Q || c == SINGLE_Q) && m->state != OPEN_QUOTE)
	{
		m->quote = c;
		return (OPEN_QUOTE);
	}
	if (c == m->quote && m->state == OPEN_QUOTE)
		return (CLOSE_QUOTE);
	return (DEFAULT);
}

size_t	token_len(t_main *m, t_node *a)
{	
	t_node	*tmp;
	size_t	len;

	len = 0;
	tmp = a;
	while (tmp && m->type == tmp->type)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}
