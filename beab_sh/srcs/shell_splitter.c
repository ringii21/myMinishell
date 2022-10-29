/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:32:10 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/29 05:15:01 by abonard          ###   ########.fr       */
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
	printf("quote parkour i == %lu\n", i);
	return (i);
}

static char	**count_args(char *s, t_main *m)
{
	size_t		words;
	size_t		i;
	char		**ret;

	words = 0;
	i = 0;
	m->quote = 0;
	m->state = S_DEFAULT;
	while (s[i])
	{
		m->state = is_state(s[i], m);
		if (s[i] != SPACE)
		{
			if (m->state == S_DEFAULT)
				i += default_parkour(s + i, m);
			else if (m->state == S_OPEN_QUOTE && s[i++] == m->quote)
				i += quote_parkour(s + i, m);
			printf("words splitter : s[%02lu] = %d\n", i, s[i]);
			words++;
		}
		m->state = is_state(s[i], m);
		if (s[i] == '\0')
			break ;
		i++;
	}
	ret = ft_calloc(words + 1, sizeof(char *));
	ret[words] = 0;
	printf("words == %lu\n", words);
	printf("..................\n");
	return (ret);
}

void	arg_splitter(char *s, t_main *m)
{	
/* 	m->k = m->j;
 	while (s[m->k] && s[m->k] != c && is_state(s[m->k + 1], m) == m->state)
		m->k++; */
	if (m->j < m->k)
	{
		if (m->state == S_OPEN_QUOTE)
			m->stab[m->index] = ft_substr(s, (unsigned int)m->j, (m->k - 1) - m->j);
		if (m->state == S_DEFAULT)
			m->stab[m->index] = ft_substr(s, (unsigned int)m->j, m->k - m->j);
		printf("m->stab[%02lu] = [%s]\n", m->index, m->stab[m->index]);
		m->index++;
		m->j = m->k - 1;
	}
}

char	**shell_splitter(char *s, t_main *m)
{
	m->index = 0;
	m->j = 0;
	m->k = 0;
	m->stab = count_args(s, m);
	m->state = S_DEFAULT;
	m->quote = 0;
	while (s[m->j])
	{	
		m->state = is_state(s[m->j], m);
		if (s[m->j] != SPACE)
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
			arg_splitter(s, m);
		}
		if (s[m->j + 1] == '\0')
			break ;
		m->state = is_state(s[m->j], m);
		m->j++;
	}
	return (m->stab);
}
