/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:01:02 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/08 15:32:07 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	split_args(t_token *parser, char *str)
{
	int		i;
	int 	j;
	char 	**tab;

	i = 0;
	while (parser->cmds_av && parser->cmds_av[i])
		i++;
	j = 0;
	tab = xmalloc(sizeof(char *) * ((unsigned long)i + 2));
	if (tab == NULL)
		return ;
	while (j < i)
	{
		tab[j] = parser->cmds_av[j];
		j++;
	}
	tab[j++] = str;
	tab[j] = NULL;
	if (parser->cmds_av != NULL)
		free(parser->cmds_av);
	parser->cmds_av = tab;

}

char *ft_strdupcat(char *s, char *o, int len)
{
	int		i;
	int		j;
	char	*n;

	n = xmalloc(ft_strlen(s) + (size_t)len + 2);
	if (n == NULL)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		n[i] = s[i];
		i++;
	}
	j = 0;
	while (j < len)
	{
		n[i + j] = o[j];
		j++;
	}
	n[i + j] = 0;
	if (s)
		free(s);
	return (n);
}
