/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:45:35 by abonard           #+#    #+#             */
/*   Updated: 2022/12/13 15:18:54 by seozcan          ###   ########.fr       */
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
	int		i;
	t_env	*tmp;
	
	tmp = env;
	if (!is_forked)
		return ;
	ft_sort_env(&tmp);
	while (tmp)
	{
		i = 0;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(tmp->var, STDOUT_FILENO);
		if (tmp->cont)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			while (tmp->cont[i])
			{
				if (tmp->cont[i] == '"' || tmp->cont[i] == '\\')
					ft_putstr_fd("\\", STDOUT_FILENO);
				ft_putchar_fd(tmp->cont[i], STDOUT_FILENO);
				i++;
			}
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		tmp = tmp->next;
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
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(namevar, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
		}
	}
	return (1);
}
