/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:32:10 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/29 07:15:55 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	default_parkour(char *s, t_main *m)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != SPACE && is_state(s[i + 1], m) == m->state)
		i++;
	return (i);
}

size_t	quote_parkour(char *s, t_main *m)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != m->quote)
		i++;
	return (i);
}

void	count_args(char *s, t_main *m)
{
	m->index = 0;
	m->i = 0;
	m->quote = 0;
	m->state = S_DEFAULT;
	while (s[m->i])
	{
		m->state = is_state(s[m->i], m);
		if (s[m->i] != SPACE)
		{
			if (m->state == S_DEFAULT)
				m->i += default_parkour(s + m->i, m);
			else if (m->state == S_OPEN_QUOTE && s[m->i++] == m->quote)
				m->i += quote_parkour(s + m->i, m);
			m->index++;
		}
		m->state = is_state(s[m->i], m);
		if (s[m->i] == '\0')
			break ;
		m->i++;
	}
	m->stab = ft_calloc(m->index + 1, sizeof(char *));
	m->stab[m->index] = 0;
}

void	arg_splitter(char *s, t_main *m)
{
	m->k = m->j;
	if (m->state == S_DEFAULT)
		m->k += default_parkour(s + m->k, m);
	else if (m->state == S_OPEN_QUOTE && m->j <= m->k)
	{
		if (s[m->j++] == m->quote)
			m->k += quote_parkour(s + m->j, m);
		m->k++;
	}
	m->k++;
	if (m->j < m->k)
	{
		if (m->state == S_OPEN_QUOTE)
			m->stab[m->index]
				= ft_substr(s, (unsigned int)m->j, (m->k - 1) - m->j);
		if (m->state == S_DEFAULT)
			m->stab[m->index] = ft_substr(s, (unsigned int)m->j, m->k - m->j);
		m->index++;
		m->j = m->k - 1;
	}
}

char	**shell_splitter(char *s, t_main *m)
{
	count_args(s, m);
	m->index = 0;
	m->j = 0;
	m->k = 0;
	m->state = S_DEFAULT;
	m->quote = 0;
	while (s[m->j])
	{	
		m->state = is_state(s[m->j], m);
		if (s[m->j] != SPACE)
			arg_splitter(s, m);
		if (s[m->j] == '\0')
			break ;
		m->state = is_state(s[m->j], m);
		m->j++;
	}
	return (m->stab);
}
