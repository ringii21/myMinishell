#include "../inc/minishell.h"

void	ft_close_fd(t_token *o)
{
	t_redir	*tmp;

	tmp = o->file;
	while (tmp)
	{
		if (tmp->type && tmp->type != DEFAULT && tmp->type != R_REDIR_IN)
			close(tmp->fd);
		tmp = tmp->next;
	}
}

void	ft_close_pipe(t_token *o)
{
	t_redir	*tmp;

	ft_close_fd(o);
	tmp = o->file;
	while (tmp)
	{
		if (tmp->type == R_REDIR_IN)
		{
			close(tmp->fd_pipe[0]);
			close(tmp->fd_pipe[1]);
		}
		tmp = tmp->next;
	}
	if (o->prev && o->prev->is_pipe == 1)
		close(o->prev->pipe_fd[0]);
	if (!o->is_pipe)
		return ;
	close(o->pipe_fd[1]);
	if (o->next == NULL)
		close(o->pipe_fd[0]);
}