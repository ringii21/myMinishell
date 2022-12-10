/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:34:52 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/10 14:06:17 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell(t_main *m)
{
	char	*prompt;

	prompt = NULL;
	while (1)
	{
		m->line = readline(ft_strjoin(getcwd(prompt, 4096), "$ "));
		if (m->line)
		{
			m->t = parser(m);
			print_tokens(m->t);
			job(m);
			ft_flush(m->t);
		}
		add_history(m->line);
		free(m->line);
//		free(prompt);
	}
}

int	main(int ac, char **av, char **envp)
{	
	t_main	m;

	if (ac != 1)
	{	
		av[1] = ft_strjoin(av[1], ": arguments not allowed.\n");
		ft_putstr_fd(av[1], 2);
		return (0);
	}
	if (set_signals() == 1)
		return (1);
	//shlvl_up(envp);
	m.env = put_env(envp);
	minishell(&m);
	return (0);
}
