/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:02:31 by abonard           #+#    #+#             */
/*   Updated: 2022/10/10 22:00:49 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_export_var(t_main *m, bool is_forked)
{
	char	*namevar;
	char	*value;
	int		i;
	int		j;

	i = 1;
	while (i < m->o.cmd_ac)
	{
		j = 0;
		namevar = NULL;
		value = NULL;
		namevar = ft_strdup(m->o.cmd_flags[i]);
		while (namevar[j])
		{
			if (namevar[j] == '=')
				namevar[j] = 0;
			else
				j++;
		}
		if (m->o.cmd_flags[i][j])
			value = namevar + j + 1;
		ft_check_and_export(namevar, value, m->env, is_forked);
		i++;
	}
	return (0);
}

int	ft_export(t_main *m, bool is_forked)
{
	int	ret;

	ret = 0;
	m->o.cmd_flags = ft_split(m->o.cmds[0], ' ');
	m->o.cmd_ac = ft_tablen(m->o.cmd_flags);
	if (m->o.cmd_ac < 2)
	{
		ft_print_declare(m->env, is_forked);
		return (ret);
	}
	ret = ft_export_var(m, is_forked);
	ft_free_stab(m->o.cmd_flags);
	return (ret);
}
