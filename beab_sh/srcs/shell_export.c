/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:02:31 by abonard           #+#    #+#             */
/*   Updated: 2022/12/15 21:41:06 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_export_var(t_token *t, t_env *env, bool is_forked)
{
	char	*namevar;
	char	*value;
	size_t	i;
	int		j;

	i = 1;
	while (i < t->cmd_ac)
	{
		j = 0;
		namevar = NULL;
		value = NULL;
		namevar = ft_strdup(t->cmds_av[i]);
		while (namevar[j])
		{
			if (namevar[j] == '=')
				namevar[j] = 0;
			else
				j++;
		}
		if (t->cmds_av[i][j])
			value = namevar + j + 1;
		ft_check_and_export(namevar, value, env, is_forked);
		i++;
		free(namevar);
	}
	return (0);
}

int	ft_export(t_token *t, t_env *env, bool is_forked)
{
	int	ret;

	ret = 0;
	if (t->cmd_ac < 2)
	{
		ft_print_declare(env, is_forked);
		return (ret);
	}
	ret = ft_export_var(t, env, is_forked);
	return (ret);
}
