/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wac <wac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:34:52 by seozcan           #+#    #+#             */
/*   Updated: 2022/11/17 14:35:03 by wac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void zeubi(char **str)
{
	int i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

void ft_fill_ac(t_obj *obj)
{
	while (obj != NULL)
	{
		if (obj->cmds_av)
		{
			obj->cmd_ac = ft_tablen(obj->cmds_av);
		}
		obj = obj->next;
	}
}

void	minishell(t_main *m)
{
	char *prompt = NULL;
	while (1)
	{
		write(1, "$", 1);
		m->line = readline(prompt);
		if (m->line)
		{
			m->o = ft_parcing(m);
			if (m->o == NULL)
				exit(1);
			ft_fill_ac(m->o);
			job(m);
			ft_flush(m->o);
		}
		add_history(m->line);
		free(m->line);
		free(prompt);
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
