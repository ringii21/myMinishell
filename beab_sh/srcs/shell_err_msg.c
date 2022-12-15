/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_err_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:41:52 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/15 17:42:32 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	ft_putstr_fd(": permission denied.\n", 2);
	g_status = 1;
	return (1);
}

void	ft_error_msg(char *err_msg)
{
	ft_putstr_fd(MINI_MSG, STDERR_FILENO);
	if (ft_strnstr(strerror(errno), "Success", 7) == 0)
		perror(err_msg);
}
