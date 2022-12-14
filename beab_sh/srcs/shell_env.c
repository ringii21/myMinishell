/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:41:28 by abonard           #+#    #+#             */
/*   Updated: 2022/12/14 22:29:14 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*put_env(char **envp)
{
	int		i;
	t_env	*tmp;
	t_env	*res;

	if (!envp || !envp[0])
	{
		res = ft_if_env_empty();
		return (res);
	}
	i = 1;
	res = fill_env(envp[0]);
	tmp = res;
	while (envp[i])
	{
		tmp->next = fill_env(envp[i]);
		tmp = tmp->next;
		i++;
	}
	return (res);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp);
	}
	env = NULL;
	free(env);
}

t_env	*ft_add_new(char *varname, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env) * 1);
	new->var = ft_strdup(varname);
	new->cont = ft_strdup(value);
	new->total = ft_strjoin(varname, "=");
	new->total = ft_strjoin(new->total, value);
	new->next = NULL;
	return (new);
}

int	ft_add_env(char *namevar, char *value, t_env *env)
{
	t_env	*newline;
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (1);
	if (ft_strcmp(namevar, "=") == 0)
		return (1);
	newline = ft_add_new(namevar, value);
	if (newline == NULL)
		return (1);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newline;
	return (0);
}

int	ft_create_o_replace(char *namevar, char *value, t_env *env)
{
	t_env	*tmp;
	char	*data;

	tmp = env;
	data = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, namevar) == 0)
		{
			free(tmp->cont);
			tmp->cont = ft_strdup(value);
			free(tmp->total);
			data = ft_strjoin("=", value);
			tmp->total = ft_strjoin(namevar, data);
			free(data);
			if (tmp->cont == NULL || tmp->total == NULL)
				return (1);
			return (0);
		}
		tmp = tmp->next;
	}
	if ((ft_add_env(namevar, value, env)) == 1)
		return (1);
	return (0);
}
