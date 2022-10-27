/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:45:35 by abonard           #+#    #+#             */
/*   Updated: 2022/10/27 16:57:35 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_swap_list(t_env **begin, t_env *last)
{
	t_env	*tmp;

	tmp = *begin;
	*begin = last->next;
	tmp->next = last->next->next;
	(*begin)->next = tmp;
}

void	ft_sort_env(t_env **begin)
{
	t_env	*end;
	t_env	*prev;

	prev = NULL;
	end = *begin;
	while (end && end->next)
	{
		if (ft_strcmp(end->var, end->next->var) > 0)
		{
			if (prev == NULL)
				ft_swap_list(begin, end);
			else
				ft_swap_list(&(prev->next), end);
			end = *begin;
			prev = NULL;
		}
		else
		{
			prev = end;
			end = end->next;
		}
	}
}

void	ft_print_declare(t_env *env, bool is_forked)
{
	int	i;

	if (!is_forked)
		return ;
	ft_sort_env(&env);
	while (env)
	{
		i = 0;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->var, 1);
		if (env->cont)
		{
			ft_putstr_fd("=\"", 1);
			while (env->cont[i])
			{
				if (env->cont[i] == '"' || env->cont[i] == '\\')
					ft_putstr_fd("\\", 1);
				ft_putchar_fd(env->cont[i], 1);
				i++;
			}
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
}

int	ft_checkname(char *namevar)
{
	if (ft_isdigit(namevar[0]) == 1)
		return (0);
	while (*namevar)
	{
		if (ft_isalnum(*namevar) == 0 && *namevar != '_')
			return (0);
		namevar++;
	}
	return (1);
}

int	ft_check_and_export(char *namevar, char *value, t_env *env, bool is_forked)
{
	if (namevar == NULL || value == NULL)
		return (0);
	if (ft_checkname(namevar) == 1)
	{
		ft_add_env(namevar, value, env);
		return (0);
	}
	if (is_forked)
	{
		ft_putstr_fd("export: not valid identifier", 2);
		if (namevar && *namevar)
		{
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(namevar, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	return (1);
}
