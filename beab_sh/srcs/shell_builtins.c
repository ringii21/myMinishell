/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:26 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/03 18:52:58 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != 0)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

int	ft_echo(void)
{
	return (0);
}

int	ft_cd(t_main *m)
{
	chdir(m->line);
	return (0);
}

int	ft_pwd(char **envp)
{
	char	*path;

	(void)envp;
	path = getenv("PWD");
	if (path == NULL)
	{
		ft_putstr_fd("variable not found\n", 2);
		return (1);
	}
	printf("%s\n", path);
	return (0);
}

