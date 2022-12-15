/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:42:16 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/15 14:09:56 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	shlvl_up(t_main *m)
{
	int		res;
	char	*value;

	if (get_cont("SHLVL", m->env) == NULL)
		return ;
	res = ft_atoi(get_cont("SHLVL", m->env));
	res++;
	value = ft_itoa(res);
	ft_create_o_replace("SHLVL", value, m->env);
	free(value);
}
