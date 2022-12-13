/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:34:52 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/12 22:33:41 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell(t_main *m)
{
	while (!m->exit)
	{
		m->line = 0;
		m->line = readline(ft_strjoin(getcwd(m->prompt, 4096), "$ "));
 		if (!m->line[0])
		{
			free(m->line);
			ft_putstr_fd("exit", STDERR_FILENO);
			m->exit = 1;
		}
		else if (m->line)
		{
			m->t = parser(m);
			print_tokens(m->t);
			if (m->t)
				job(m);
			ft_flush(m->t);
			add_history(m->line);
			free(m->line);
			free(m->prompt);
		}
	}
}

int	main(int ac, char **av, char **envp)
{	
	t_main	m;

	m = (t_main){0};
	if (ac != 1)
	{	
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		av[1] = ft_strjoin(av[1], ": arguments not allowed.\n");
		ft_putstr_fd(av[1], STDERR_FILENO);
		return (0);
	}
	if (set_signals() == 1 || set_sig() == 1)
		return (1);
	m.env = put_env(envp);
	shlvl_up(m.env);
	minishell(&m);
	free_env(m.env);
	return (0);
}
