/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:30:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/08 16:20:19 by seozcan          ###   ########.fr       */
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

void	inside_quotes(t_main *m, t_stack *tmp)
{
	while (m->line[m->i] && !is_quote(m->line[m->i], m))
	{
		put_back(tmp, (unsigned int)is_operator(m->line[m->i], m),
			ft_substr(m->line, m->i, 1));
		m->i++;
	}
}

void	find_types(t_main *m, t_stack *tmp)
{	
	m->i = 0;
	while (m->line[m->i] && ft_isascii(m->line[m->i]))
	{
		m->state = is_quote(m->line[m->i], m);
		put_back(tmp, (unsigned int)is_operator(m->line[m->i], m),
			ft_substr(m->line, m->i, 1));
		m->i++;
		if (m->line[m->i] && m->state == OPEN_QUOTE)
			inside_quotes(m, tmp);
	}
	if (m->state == OPEN_QUOTE)
		ft_putstr_fd("Error: Open quote found\n", 2);
}

void	build_token(t_main *m, t_stack *a, t_stack *b)
{
	m->i = 0;
	while (a->head)
	{
		while (a->head && a->head->type == O_SPACE)
			a->head = a->head->next;
		m->i = 0;
		m->type = a->head->type;
		m->j = (unsigned int)token_len(m, a->head);
		m->buff = xmalloc(sizeof(char) * (m->j + 1));
		m->buff[m->j] = '\0';
		while (a->head && m->type == a->head->type)
		{
			m->buff[m->i] = a->head->arg[0];
			a->head = a->head->next;
			m->i++;
		}
		put_back(b, m->type, ft_substr(m->buff, 0, m->i));
		free(m->buff);
	}
}

int	lexer(t_main *m)
{	
	t_stack	*tmp_a;
	t_stack	*tmp_b;

	m->state = DEFAULT;
	m->lexicon = xmalloc(sizeof(t_stack));
	m->tokens = xmalloc(sizeof(t_stack));
	init_stack(m->lexicon);
	init_stack(m->tokens);
	tmp_a = m->lexicon;
	tmp_b = m->tokens;
	find_types(m, tmp_a);
	if (m->state == OPEN_QUOTE)
	{
		free(m->lexicon);
		return (0);
	}
	build_token(m, tmp_a, tmp_b);
	free_stack(m->lexicon);
	return (1);
}
