/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:16:05 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/15 21:12:32 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_pipes(t_token *t)
{
	if (t->prev != NULL)
	{
		close(t->prev->pipe_fd[0]);
		close(t->prev->pipe_fd[1]);
	}
}

int	dup_fd(t_token *t)
{
	t_redir	*tmp;

	tmp = t->file;
	while (tmp)
	{
		if (tmp->type == R_REDIR_OUT || tmp->type == REDIR_OUT)
			dup2(tmp->fd, 1);
		else if (tmp->type == R_REDIR_IN || tmp->type == REDIR_IN)
		{
			if (tmp->type == REDIR_IN)
				dup2(tmp->fd, 0);
			if (tmp->type == R_REDIR_IN)
			{
				tmp->fd = open(tmp->file_name, O_RDONLY | O_CREAT, 0644);
				if (tmp->fd < 0)
					return (0);
				if (dup2(tmp->fd, 0) < 0)
					return (0);
				close(tmp->fd);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	dup_pipes(t_token *t, int *is_pipe)
{
	if (t->prev != NULL)
	{
		if (dup2(t->prev->pipe_fd[0], 0) < 0)
			return (0);
		close(t->prev->pipe_fd[0]);
		close(t->prev->pipe_fd[1]);
	}
	if (t->next != NULL)
	{
		if (dup2(t->pipe_fd[1], STDOUT_FILENO) < 0)
			return (0);
		close(t->pipe_fd[0]);
		close(t->pipe_fd[1]);
	}
	if (!dup_fd(t))
		return (0);
	*is_pipe = 1;
	return (1);
}

int	child_process(t_token *t, t_env *env, bool builtin)
{	
	char	**env_tab;

	if (!dup_pipes(t, &(t->is_pipe_open)))
		ft_mini_exit(EXIT_FAILURE, t, env);
	if (builtin)
		ft_mini_exit(exec_builtin(t, env, true), t, env);
	if (t->cmds_av == NULL || t->cmds_av[0] == NULL)
	{
		t->is_error = true;
		ft_mini_exit(EXIT_FAILURE, t, env);
	}
	if (t->is_pipe)
		close(t->pipe_fd[0]);
	env_tab = NULL;
	env_tab = ft_env_to_tab(env);
	if (execve(t->bin_path, t->cmds_av, env_tab) == -1)
	{
		ft_free_stab(env_tab);
		if (errno == 13)
			return (-1);
	}
	ft_mini_exit(EXIT_FAILURE, t, env);
	return (0);
}
