/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_err_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:41:52 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/16 22:19:09 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	return_error_cmd_nf(t_token *t)
{
	ft_putstr_fd(MINI_MSG, STDERR_FILENO);
	ft_putstr_fd(t->cmds_av[0], STDERR_FILENO);
	ft_putstr_fd(ERR_CMD, STDERR_FILENO);
	g_status = 127;
	return (127);
}

int	return_error_no_file(t_redir *file)
{
	ft_putstr_fd(MINI_MSG, STDERR_FILENO);
	ft_putstr_fd(file->file_path, STDERR_FILENO);
	ft_putstr_fd(ERR_FILE, STDERR_FILENO);
	close(file->fd);
	g_status = 127;
	return (1);
}

int	return_error_access_denied(t_redir *file)
{
	ft_putstr_fd(MINI_MSG, STDERR_FILENO);
	ft_putstr_fd(file->file_path, STDERR_FILENO);
	ft_putstr_fd(ERR_PERM, STDERR_FILENO);
	g_status = 1;
	return (1);
}

int	ft_error_msg(int ret, char *err_msg)
{
	ft_putstr_fd(MINI_MSG, STDERR_FILENO);
	if (ft_strnstr(strerror(errno), "Success", 7) == 0)
		if (err_msg)
			perror(err_msg);
	g_status = errno;
	return (ret);
}
