/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:42:16 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/13 21:19:26 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	shlvl_up(t_main *m)
{
	int 	res;
	
	if (get_cont("SHLVL", m->env) == NULL)
		return ;
	res = ft_atoi(get_cont("SHLVL", m->env));
	res++;
	ft_exec_unset("SHLVL", m->env);
	ft_add_env("SHLVL", ft_itoa(res), m->env);
}