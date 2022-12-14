/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:34:52 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/14 16:31:44 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
int g_status;

void	minishell(t_main *m)
{	
	char *prompt;
	char *cwd;

	prompt = NULL;
	cwd = NULL;
	 while (1)
	{
		cwd = getcwd(NULL, 4096);
		prompt = ft_strjoin(cwd, "$ ");
		free(cwd);
		m->line = readline(prompt);
		m->line = ft_strtrim(m->line, " \f\t\n\r\v");
		if (!m->line)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		if (m->line && m->line[0] != '\0')
		{
			m->t = parser(m);
			if (m->t == NULL && m->t->is_error == false)
				exit(1);
//			print_tokens(m->t);
			if (m->t)
				job(m);
			if (m->t->is_error == true)
				free(m->t);
			else
				ft_flush(m->t);
		}
		add_history(m->line);
		free(m->line);
		m->line = NULL;
		free(prompt);
		m->t = NULL;
	}
	rl_clear_history(); 
	
/* 	char *prompt = NULL;
	char *cwd = NULL;

	while (1)
	{
		cwd = getcwd(NULL, 4096);
		//write(1, "$", 1);
		prompt = ft_strjoin(cwd, "$ ");
		free(cwd);
		m->line = readline(prompt);
		m->line = ft_strtrim(m->line, " \f\t\n\r\v");
		if (!m->line)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		if (m->line && m->line[0] != '\0')
		{
			m->t = parser(m);
			if (m->t == NULL && m->t->is_error == false)
				exit(1);
			//ft_fill_ac(m->t);
			job(m);
			if (m->t->is_error == true)
				free(m->t);
			else
				ft_flush(m->t);
		}
		add_history(m->line);
		free(m->line);
		m->line = NULL;
		free(prompt);
		m->t = NULL;
	} */
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
	//shlvl_up(&m);
	minishell(&m);
	free_env(m.env);
	return (0);
}
