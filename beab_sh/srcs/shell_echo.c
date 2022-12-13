/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:12:20 by abonard           #+#    #+#             */
/*   Updated: 2022/12/13 13:47:44 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_flag(char *flags)
{
	int	i;

	i = 0;
	if (flags[i] != '-')
		return (0);
	i++;
	while (flags[i])
	{
		if (flags[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exec_echo(t_token *t, bool flag)
{
	size_t	i;

	i = 1;
	if (flag == true)
		i = 2;
	while (t->cmds_av[i] && i < t->cmd_ac)
	{
		ft_putstr_fd(t->cmds_av[i], 1);
		if (i + 1 < t->cmd_ac)
			ft_putchar_fd(' ', 1);
		else if (i + 1 == t->cmd_ac && flag == true)
			return (0);
		else if (i + 1 == t->cmd_ac && flag == false)
		{
			ft_putchar_fd('\n', 1);
			return (0);
		}
		i++;
	}
	return (-1);
}

int	ft_echo(t_token *t)
{
	bool	flag;

	flag = false;
	if (t->cmd_ac < 2)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (ft_is_flag(t->cmds_av[1]) == 1)
		flag = true;
	if (t->cmd_ac == 2 && flag == true)
		return (0);
	else
	{
		if (ft_exec_echo(t, flag) < 0)
			return (-1);
	}
	return (0);
}
