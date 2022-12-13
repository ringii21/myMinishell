/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:16:05 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/13 13:52:47 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_pipes(t_token *t)
{
	t_redir	*tmp;

	ft_close_fd(t);
	tmp = t->file;
	while (tmp)
	{
		if (tmp->type == R_REDIR_IN)
		{
			close(tmp->fd_pipe[0]);
			close(tmp->fd_pipe[1]);
		}
		tmp = tmp->next;
	}
	if (t->prev && t->prev->is_pipe == 1)
		close(t->prev->pipe_fd[0]);
	if (!t->is_pipe)
		return ;
	close(t->pipe_fd[1]);
	if (t->next == NULL)
		close(t->pipe_fd[0]);
}

void	dup_fd(t_token *t)
{
	t_redir	*tmp;

	tmp = t->file;
	while (tmp)
	{
		if (tmp->type == R_REDIR_OUT || tmp->type == REDIR_OUT)
			dup2(tmp->fd, STDOUT_FILENO);
		else if (tmp->type == R_REDIR_IN || tmp->type == REDIR_IN)
		{
			if (tmp->type == REDIR_IN)
				dup2(tmp->fd, STDIN_FILENO);
			if (tmp->type == R_REDIR_IN)
			{
				dup2(tmp->fd_pipe[0], STDIN_FILENO);
				close(tmp->fd_pipe[0]);
			}
		}
		tmp = tmp->next;
	}	
}

int	dup_pipes(t_token *t, int *is_pipe)
{
	if (t->is_pipe && dup2(t->pipe_fd[1], 1) < 0)
		return (0);
	if (t->prev && t->prev->is_pipe && dup2(t->prev->pipe_fd[0], 0) < 0)
		return (0);
	dup_fd(t);
	*is_pipe = 1;
	return (1);
}

int	child_process(t_token *t, t_env *env, bool builtin)
{
	char	**paths;
	
	if (!dup_pipes(t, &(t->is_pipe_open)))
		exit(EXIT_FAILURE);
	if (builtin)
		exit(exec_builtin(t, env, true));
	if (!t->cmds_av[0])
		exit(EXIT_FAILURE);
	if (t->is_pipe)
		close(t->pipe_fd[0]);
	paths =  ft_env_to_tab(env);
	if (execve(t->cmds_av[0], t->cmds_av, paths) != -1)
	{
		if (errno == 13)
			return (-1);
		ft_free_stab(paths);
		ft_error(t->cmds_av[0]);
	}
//	exit(EXIT_FAILURE);
	return (0);
}
