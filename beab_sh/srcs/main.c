/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:34:52 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/17 00:32:20 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_status;

void	ft_check_line(t_main *m)
{
	if (m->line && m->line[0] != '\0')
	{
		m->t = parser(m);
		free_parser(m->p);
		if (!m->t)
			ft_mini_exit(1, NULL, m->env);
		else
		{
			job(m);
			ft_flush(m->t);
		}
	}	
}

void	minishell(t_main *m)
{	
	char	*cwd;

	cwd = NULL;
	while (1)
	{
		cwd = getcwd(NULL, 0);
		m->prompt = ft_strjoin(cwd, "$ ");
		free(cwd);
		m->line = readline(m->prompt);
		free(m->prompt);
		if (!m->line)
		{
			ft_putstr_fd(EXIT_MSG, STDERR_FILENO);
			break ;
		}
		ft_check_line(m);
		if (ft_isprint(m->line[0]))
			add_history(m->line);
		free(m->line);
		m->line = NULL;
		m->t = NULL;
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **envp)
{	
	t_main	m;

	g_status = 0;
	m = (t_main){0};
	if (ac != 1)
	{	
		errno = E2BIG;
		return (ft_error_msg(0, av[1]));
	}
	if (set_signals() == 1 || set_sig() == 1)
		return (1);
	m.env = put_env(envp);
	shlvl_up(&m);
	minishell(&m);
	free_env(m.env);
	return (0);
}
