#include "../inc/minishell.h"

void	ft_dup_fd(t_token *o)
{
	t_redir	*tmp;

	tmp = o->file;
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
				dup2(tmp->fd_pipe[0], 0);
				close(tmp->fd_pipe[0]);
			}
		}
		tmp = tmp->next;
	}	
}

int	dup_pipes(t_token *o, int *is_pipe)
{
	if (o->is_pipe && dup2(o->pipe_fd[1], 1) < 0)
		return (0);
	if (o->prev && o->prev->is_pipe && dup2(o->prev->pipe_fd[0], 0) < 0)
		return (0);
	ft_dup_fd(o);
	*is_pipe = 1;
	return (1);
}

int	ft_child_play(t_token *o, t_env *env, bool builtin)
{
	if (!dup_pipes(o, &(o->is_pipe_o)))
		exit(EXIT_FAILURE);
	if (builtin)
		exit(exec_builtin(o, env, true));
	if (!o->cmds_av[0])
		exit(EXIT_FAILURE);
	if (o->is_pipe)
		close(o->pipe_fd[0]);
	if (execve(o->cmds_av[0], o->cmds_av, ft_env_to_tab(env)) == -1)
	{
		if (errno == 13)
			return (-1);
	}
	exit(EXIT_FAILURE);
	return (0);
}