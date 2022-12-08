/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:01:02 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/08 17:59:15 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*last_error(bool set, int err)
{
	static char	*value;

	if (set)
	{
		if (value)
			free(value);
		value = ft_itoa(err);
	}
	else if (!value)
		value = ft_strdup("0");
	return (value);
}

void	split_args(t_token *t, char *str)
{
	int		i;
	int 	j;
	char 	**tab;

	i = 0;
	while (t->cmds_av && t->cmds_av[i])
		i++;
	j = 0;
	tab = xmalloc(sizeof(char *) * ((unsigned long)i + 2));
	if (tab == NULL)
		return ;
	while (j < i)
	{
		tab[j] = t->cmds_av[j];
		j++;
	}
	tab[j++] = str;
	tab[j] = NULL;
	if (t->cmds_av != NULL)
		free(t->cmds_av);
	t->cmds_av = tab;
}

char *ft_strdupcat(char *s, char *t, int len)
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
		n[i + j] = t[j];
		j++;
	}
	n[i + j] = 0;
	if (s)
		free(s);
	return (n);
}
