/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:34:52 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/08 21:09:54 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_fill_ac(t_token *t)
{
	while (t != NULL)
	{
		if (t->cmds_av)
			t->cmd_ac = ft_tablen(t->cmds_av);
		t = t->next;
	}
}

void	minishell(t_main *m)
{
	char	*prompt;

	prompt = NULL;
	while (1)
	{
		m->line = readline(ft_strjoin(getcwd(prompt, 4096), "$ "));
		if (m->line)
		{
			m->t = ft_parsing(m);
			if (m->t == NULL)
				exit(1);
			ft_fill_ac(m->t);
			job(m);
			ft_flush(m->t);
		}
		add_history(m->line);
		free(m->line);
	}
}

int	main(int ac, char **av, char **envp)
{	
	t_main	m;

	(void)av;
	(void)ac;
	if (set_signals() == 1)
		return (1);
	m.env = put_env(envp);
	minishell(&m);
	return (0);
}
