/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:33:12 by abonard           #+#    #+#             */
/*   Updated: 2022/12/16 22:00:09 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_head(t_env *env)
{	
	t_env	*tmp;

	tmp = env->next;
	free(env->var);
	env->var = tmp->var;
	free(env->cont);
	env->cont = tmp->cont;
	free(env->total);
	env->total = tmp->total;
	env->next = tmp->next;
	free(tmp);
}

int	ft_delete_first_elmt(t_env *env)
{
	if (env->next == NULL)
	{
		free(env->var);
		free(env->cont);
		free(env->total);
		env->var = ft_strdup("");
		env->cont = ft_strdup("");
		env->total = ft_strdup("");
		if (env->var == NULL || env->cont == NULL || env->total == NULL)
		{
			ft_putstr_fd("malloc failed\n", STDERR_FILENO);
			return (1);
		}
	}
	else
		free_head(env);
	return (0);
}

void	ft_free_var(t_env *prev)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = prev->next;
	free(tmp->var);
	free(tmp->cont);
	free(tmp->total);
	prev->next = tmp->next;
	free(tmp);
}

int	ft_exec_unset(char *namevar, t_env *env)
{
	t_env	*prev;

	if (env == NULL)
	{
		ft_putstr_fd("environement is empty\n", STDERR_FILENO);
		return (1);
	}
	prev = env;
	if (ft_strcmp(namevar, prev->var) == 0)
	{
		ft_delete_first_elmt(env);
		return (0);
	}
	while (prev != NULL)
	{
		if (prev->next != NULL && ft_strcmp((prev->next)->var, namevar) == 0)
			break ;
		prev = prev->next;
	}
	if (prev == NULL)
		return (0);
	ft_free_var(prev);
	return (0);
}

int	ft_unset(t_token *t, t_env *env, bool is_forked)
{
	size_t	i;
	int		res;

	i = 1;
	if (t->cmd_ac >= 2)
	{
		while (t->cmds_av[i] && i < t->cmd_ac)
		{
			ft_exec_unset(t->cmds_av[i], env);
			i++;
		}
		res = 0;
	}
	else
	{
		if (is_forked)
			ft_putstr_fd("unset: Not enough arguments.\n", STDERR_FILENO);
		res = 1;
	}
	return (res);
}
