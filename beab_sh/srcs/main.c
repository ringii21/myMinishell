/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:34:52 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/14 16:36:40 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int g_status;

void	ft_check_line(t_main *m)
{
	if (m->line && m->line[0] != '\0')
	{
		m->t = parser(m);
		if (m->t == NULL && m->t->is_error == false)
			exit(1);
//		print_tokens(m->t);
		if (m->t)
			job(m);
		if (m->t->is_error == true)
			free(m->t);
		else
			ft_flush(m->t);
	}	
}

void	minishell(t_main *m)
{	
	char *cwd;

	cwd = NULL;
	while (1)
	{
		cwd = getcwd(NULL, 0);
		m->prompt = ft_strjoin(cwd, "$ ");
		free(cwd);
		m->line = readline(m->prompt);
		m->line = ft_strtrim(m->line, " \f\t\n\r\v");
		if (!m->line)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		ft_check_line(m);
		add_history(m->line);
		free(m->line);
		m->line = NULL;
		free(m->prompt);
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
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		av[1] = ft_strjoin(av[1], ": arguments not allowed.\n");
		ft_putstr_fd(av[1], STDERR_FILENO);
		return (0);
	}
	if (set_signals() == 1 || set_sig() == 1)
		return (1);
	m.env = put_env(envp);
	shlvl_up(&m);
	minishell(&m);
	free_env(m.env);
	return (0);
}
