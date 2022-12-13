/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:16:27 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/11 18:38:11 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_close_fd(t_token *t)
{
	t_redir	*tmp;

	tmp = t->file;
	while (tmp)
	{
		if (tmp->type && tmp->type != DEFAULT && tmp->type != R_REDIR_IN)
			close(tmp->fd);
		tmp = tmp->next;
	}
}

void	dup_redir(t_token *t)
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
				dup2(tmp->file_pipe[0], STDIN_FILENO);
				close(tmp->file_pipe[0]);
			}
		}
		tmp = tmp->next;
	}	
}

int	ft_input(t_token *t, t_env *env)
{
	t_redir	*tmp;

	(void)env;
	tmp = t->file;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
		{
			tmp->fd = open(tmp->file_path, O_RDONLY);
			if (errno == EACCES)
				return (1); // Permission denied
			else if (tmp->fd < 0)
				return (1); // No such file or directory
		}
		else if (tmp->type == R_REDIR_IN)
		{
			heredoc(t, env);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_output(t_token *t)
{
	t_redir	*tmp;

	tmp = t->file;
	while (tmp)
	{
		if (tmp->type == REDIR_OUT)
		{
			tmp->fd = open(tmp->file_path, O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (errno == EACCES)
				return (1);
		}
		else if (tmp->type == R_REDIR_OUT)
		{
			tmp->fd = open(tmp->file_path, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (errno == EACCES)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_redir(t_token *t, t_env *env)
{
	if (ft_input(t, env) == 1)
		return (1);
	if (ft_output(t) == 1)
		return (1);
	return (0);
}
