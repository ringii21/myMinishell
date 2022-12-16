/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:10:56 by abonard           #+#    #+#             */
/*   Updated: 2022/12/16 16:46:01 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_envlen(t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	*get_cont(char *name_var, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(name_var, tmp->var) == 0)
			return (tmp->cont);
		tmp = tmp->next;
	}
	return (NULL);
}

char	**ft_env_to_tab(t_env *env)
{
	char	**tab;
	t_env	*tmp;
	int		i;
	int		len;

	i = 0;
	tmp = env;
	len = ft_envlen(tmp);
	tab = ft_calloc((unsigned long)len + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	while (tmp)
	{
		tab[i] = ft_strdup(tmp->total);
		if (tab[i] == NULL)
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	return (tab);
}

t_env	*fill_env(char *is_env)
{
	t_env	*new;
	char	**tab;

	tab = NULL;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->total = ft_strdup(is_env);
	tab = NULL;
	tab = ft_split(new->total, '=');
	new->var = ft_strdup(tab[0]);
	if (new->var == NULL)
		return (NULL);
	if (tab[1])
		new->cont = ft_strdup(tab[1]);
	ft_free_stab(tab);
	return (new);
}

t_env	*ft_if_env_empty(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env) * 1);
	if (!new)
		return (NULL);
	new->var = ft_strdup("PWD");
	new->cont = getcwd(NULL, 0);
	new->total = ft_strdup(new->var);
	new->total = ft_strjoin(new->total, "=");
	new->total = ft_strjoin(new->total, new->cont);
	new->next = NULL;
	return (new);
}
