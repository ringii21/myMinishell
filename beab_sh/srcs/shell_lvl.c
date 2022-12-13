/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:42:16 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/13 14:12:10 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	shlvl_up(t_env *env)
{
	int res;
	
	if (get_cont("SHLVL", env) == NULL)
		return ;
	res = ft_atoi(get_cont("SHLVL", env));
	while (env && env->next)
	{
		if (!ft_strncmp(env->var, "SHLVL", 5))
		{
			res += 1;
			env->cont = ft_itoa(res);
			return ;
		}
		env = env->next;
	}
}