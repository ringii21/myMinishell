/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:30:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/09/26 21:37:14 by seozcan          ###   ########.fr       */
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

char	*is_in_quotes(char *s)
{
	unsigned int	i;
	size_t			j;
	int				quote;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == DOUBLE_Q || s[i] == SINGLE_Q)
		{
			quote = (int)s[i];
			j = i;
			while (s[j])
			{
				if (s[j] == DOUBLE_Q && quote == DOUBLE_Q)
					return (ft_substr(s, i, j - i + 1));
				if (s[j] == SINGLE_Q && quote == SINGLE_Q)
					return (ft_substr(s, i, j - i + 1));
				j++;
			}
			return (0);
		}
		i++;
	}
	return (0);
}

static char	**ft_strs(char const *s, int c)
{
	size_t	i;
	size_t	j;
	char	**dest;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
			j++;
		i++;
	}
	dest = malloc(sizeof(char *) * j + 1);
	if (!dest)
		return (0);
	dest[j] = 0;
	return (dest);
}

char	**tokenizr(char *src, int c)
{
	unsigned int	i;
	unsigned int	j;
	size_t			k;
	char			**dst;

	i = 0;
	k = 0;
	dst = ft_strs(src, c);
	if (!dst)
		return (0);
	while (src[i])
	{
		if (src[i] != c)
		{
			j = i;
			while (src[j] != c && src[j])
				j++;
			dst[k++] = ft_substr(src, i, j - i);
			i = j - 1;
		}
		if (src[i + 1] == '\0')
			break ;
		i++;
	}
	return (dst);
}

/* 
	-> 	find a way to keep double quotes and not cut them out 
		of the resulting string array
*/

void	lexer(t_main *m)
{
	int		i;
	char	**tokens;
	char	*operators;

	i = 0;
	m->args = xmalloc(sizeof(t_stack));
	init_stack(m->args);
	operators = ft_strdup("\t&()>|<\n");
	tokens = multi_split(m->line, operators);
	while (tokens[i] != 0)
	{
		if (ft_strcmp(tokens[i], operators))
			put_back(m->args, OPERATOR, ft_strdup(tokens[i]));
		else
			put_back(m->args, WORD, ft_strdup(tokens[i]));
		i++;
	}
	ft_free_stab(tokens);
}
