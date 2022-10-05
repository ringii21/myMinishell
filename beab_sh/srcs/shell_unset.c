/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:33:12 by abonard           #+#    #+#             */
/*   Updated: 2022/10/05 21:06:55 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_delete_first_elmt(t_env *env)
{
	t_env	*tmp;

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
			ft_putstr_fd("Malloc failed\n", 2);
			return (1);
		}
	}
	else
	{
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
	return (0);
}

int	ft_exec_unset(char *namevar, t_env *env)
{
	t_env	*tmp;
	t_env	*prev;

	prev = env;
	tmp = NULL;
	if (env == NULL)
	{
		ft_putstr_fd("environement is empty\n", 2);
		return (1);
	}
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
	tmp = prev->next;
	free(tmp->var);
	free(tmp->cont);
	free(tmp->total);
	prev->next = tmp->next;
	free(tmp);
	return (0);
}

int	ft_unset(t_main *m, bool is_forked)
{
	int	i;
	int	res;

	i = 1;
	m->o.cmd_flags = ft_split(m->o.cmds[0], ' ');
	m->o.cmd_nb = ft_tablen(m->o.cmd_flags);
	if (m->o.cmd_nb >= 2)
	{
		while (m->o.cmd_flags[i] && i < m->o.cmd_nb)
		{
			ft_exec_unset(m->o.cmd_flags[i], m->env);
			i++;
		}
		res = 0;
	}
	else
	{
		if (is_forked)
		{
			ft_putstr_fd("unset: Not enough arguments.\n", 2);
		}
		res = 1;
	}
	return (res);
}
