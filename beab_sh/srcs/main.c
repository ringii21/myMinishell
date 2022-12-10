/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ringii <ringii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:34:52 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/10 13:39:04 by ringii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	count_ac(t_token *t)
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
			m->t = parser(m);
			//print_tokens(m->t);
			count_ac(m->t);
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
