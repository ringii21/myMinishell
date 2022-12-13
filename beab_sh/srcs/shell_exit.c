/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:34:43 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/12 20:11:31 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_exit(t_main *m, t_token *t)
{
	m->exit = 1;
	ft_putstr_fd("exit", STDERR_FILENO);
	if (t->cmds_av && t->cmd_ac > 2)
	{
		m->ret = 1;
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
	}
	else if (t->cmds_av && t->cmd_ac >= 2)
	{
		if (ft_strisdigit(t->cmds_av[1]) == 1)
			m->ret = ft_atoi(t->cmds_av[1]);
		else
		{
			m->ret = 255;
			ft_putstr_fd("minishell: exit:", STDERR_FILENO);
			ft_putstr_fd(t->cmds_av[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		}
	}
	else
		m->ret = 0;
}
