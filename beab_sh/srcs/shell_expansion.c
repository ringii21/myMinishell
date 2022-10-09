/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:42:51 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/09 11:20:31 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	expansion(t_main *m)
{
	m->o.fd_in = 0;
	m->o.fd_out = 1;
	if (getenv("PATH") != NULL)
		m->o.paths = ft_split(getenv("PATH"), ':');
	m->o.cmds = ft_split(m->line, '|');
	m->o.cmd_nb = ft_tablen(m->o.cmds);
	m->o.pipe_nb = m->o.cmd_nb - 1;
	if (m->o.pipe_nb > 0)
		ft_assign_pipes(&m->o);
	m->o.index = 0;
}
