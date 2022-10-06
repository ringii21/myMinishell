/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:34:43 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/06 19:44:13 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_exit(t_main *m, bool is_forked)
{
	int	ret;

	ret = 0;
	m->o.cmd_flags = ft_split(m->o.cmds[0], ' ');
	m->o.cmd_ac = ft_tablen(m->o.cmd_flags);
	if (m->o.cmd_flags && m->o.cmd_ac > 2 && is_forked)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else if (m->o.cmd_flags && m->o.cmd_ac >= 2)
	{
		if (ft_strisdigit(m->o.cmd_flags[1]) == 1)
			ret = ft_atoi(m->o.cmd_flags[1]);
		else
		{
			if (is_forked)
				ft_putstr_fd("exit: numeric argument required\n", 2);
			return (1);
		}
	}
	if (is_forked)
		printf("exit\n");
	//ft_flush(m); free TOUT TOUT TOUT 
	exit(ret);
	return (ret);
}
