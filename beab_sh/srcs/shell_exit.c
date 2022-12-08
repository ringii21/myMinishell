/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:34:43 by seozcan           #+#    #+#             */
/*   Updated: 2022/11/16 21:46:48 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_exit(t_obj *o, bool is_forked)
{
	int	ret;

	ret = 0;
	if (o->cmds_av && o->cmd_ac > 2 && is_forked)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else if (o->cmds_av && o->cmd_ac >= 2)
	{
		if (ft_strisdigit(o->cmds_av[1]) == 1)
			ret = ft_atoi(o->cmds_av[1]);
		else
		{
			if (is_forked)
				ft_putstr_fd("exit: numeric argument required\n", 2);
			return (1);
		}
	}
	if (is_forked)
		printf("exit\n");
	exit(ret);
	return (ret);
}
