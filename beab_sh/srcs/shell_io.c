/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:16:27 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/14 23:08:57 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	return_error_no_file(t_redir *file)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(file->file_path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	close(file->fd);
	g_status = 127;
	return (1);
}

int	return_error_access_denied(t_redir *file)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(file->file_path, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	g_status = 126;
	return (1);
}

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
				return (return_error_access_denied(tmp)); // Permission denied
			else if (tmp->fd < 0)
				return (return_error_no_file(tmp)); // No such file or directory
		}
		else if (tmp->type == R_REDIR_IN)
		{
			heredoc(t, env);
			printf("Valeur de g_status: %d\n", g_status);
			if (g_status >= 128)
				return (1);
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
			tmp->fd = open(tmp->file_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
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
