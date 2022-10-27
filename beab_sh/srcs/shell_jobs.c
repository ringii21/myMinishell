/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wac <wac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:44:06 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/27 16:05:30 by wac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_process(t_main *m, t_node *token)
{
	t_token	*data;

	data = (t_token *)token->data;
	data->pid = fork();
	if (data->pid == -1)
		ft_error();
	else if (data->pid > 0)
	{
		waitpid(data->pid, 0, 0);
		kill(data->pid, SIGTERM);
	}
	else if (data->pid == 0)
	{
		if (m->pipe_ac > 0)
		{	
			pipes(token);
			if (data->id == O_PIPE)
				execute(m, data);
//			else if (data->id == O_DELEM)
//				heredoc(data, m);
		}
		else
			execute(m, data);
	}
}

void	assign_job(t_main *m)
{
	t_token	*data;

	data = NULL;
	m->index = 0;
	while (m->tokens)
	{
		data = (t_token *)m->tokens->data;
		if (is_builtin(data, m->builtins) == 1)
			exec_builtin(m, data);
		else
		{
			ft_process(m, m->tokens);
			m->index++;
		}
		m->tokens = m->tokens->next;

	}
	waitpid(-1, NULL, 0);
}

int	process_args(t_main *m)
{
	m->paths = ft_split(get_cont("PATH", m->env), ':');
	if (!create_lexicon(m))
		return (0);
	if (!create_tokens(m))
		return (0);
	return (1);
}

void	job(t_main *m)
{
	if (!process_args(m))
	{
		free_parser(m->tokens);
		return ;
	}
	print_parser(m->tokens);
	assign_job(m);
	free_nodes(&m->lexicon, &free);
	free_parser(m->tokens);
	ft_free_stab(m->paths);
}
