/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:42:16 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/10 13:13:10 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	shlvl_up(char **envp)
{
	int	i;
	int res;
	char **var;
	char *ret;
	
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "SHLVL", 5))
		{
			var = ft_split(envp[i], '=');
			res = ft_atoi(var[1]);
			res++;
			var[1] = ft_itoa(res);
			var[0] = ft_strjoin(var[0], "=");
			ret = ft_strjoin(var[0], var[1]);
			envp[i] = ft_strdup(ret);
			free(ret);
			ft_free_stab(var);
			return ;
		}
		i++;
	}
}