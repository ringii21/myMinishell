#include "../inc/minishell.h"

int	ft_input(t_obj *o, t_env *env)
{
	t_list_f	*tmp;
	(void)env;

	tmp = o->file;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
		{
			tmp->fd = open(tmp->path, O_RDONLY);
			if (errno == EACCES)
				return (1); // Permission denied
			else if (tmp->fd < 0)
				return (1); // No such file or directory
		}
		else if (tmp->type == R_REDIR_IN)
		{
			return (0);
			//ft_heredoc();
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_output(t_obj *o)
{
	t_list_f	*tmp;

	tmp = o->file;
	while (tmp)
	{
		if (tmp->type == REDIR_OUT)
		{
			tmp->fd = open(tmp->path, O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (errno == EACCES)
				return (1);
		}
		else if (tmp->type == R_REDIR_OUT)
		{
			tmp->fd = open(tmp->path, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (errno == EACCES)
				return (1); 
		}
		tmp = tmp->next;
	}
	return (0);	
}