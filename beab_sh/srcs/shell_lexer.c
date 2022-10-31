/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:30:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/29 07:19:43 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
		operators:
		- control operators: 		‘||’, ‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’,
									‘|&’, ‘(’, or ‘)’.
		- redirection operators :	< << > >> | &

		A token that doesn’t contain meta-character 
		and isn’t in quotes is a ‘word’. 
		
		A token that contains no quotes and at least
		one meta-character is an ‘operator’.
*/

t_states	is_state(char c, t_main *m)
{	
	if (c == m->quote && m->state == S_OPEN_QUOTE)
		return (S_CLOSING_QUOTE);
	if (((c == DOUBLE_Q || c == SINGLE_Q) && m->state != S_OPEN_QUOTE)
		|| m->state == S_OPEN_QUOTE)
	{
		if ((c == DOUBLE_Q || c == SINGLE_Q) && m->state != S_OPEN_QUOTE)
			m->quote = c;
		return (S_OPEN_QUOTE);
	}
	return (S_DEFAULT);
}

t_types	is_operator(char c, t_main *m)
{	
	if ((!ft_isprint(c) || c == ' ') && m->state == S_DEFAULT)
		return (T_SPACE);
	if (ft_strchr("|&><$", c) && m->state == S_DEFAULT)
		return (T_OPERATOR);
	return (T_WORD);
}

t_lexer	*fill_lexicon(t_main *m)
{
	t_lexer	*content;

	content = (t_lexer *)ft_calloc(1, sizeof(t_lexer));
	content->type = is_operator(m->line[m->i], m);
	content->arg = m->line[m->i];
	return (content);
}

int	create_lexicon(t_main *m)
{	
	m->lexicon = NULL;
	m->i = 0;
	m->state = S_DEFAULT;
	while (m->line[m->i])
	{
		m->state = is_state(m->line[m->i], m);
		putback_node(&m->lexicon, new_node(fill_lexicon(m)));
		m->i++;
	}
	if (m->state == S_OPEN_QUOTE)
	{
		ft_putstr_fd("Error: Open quote found\n", 2);
		free_nodes(&m->lexicon, &free);
		return (0);
	}
	return (1);
}
