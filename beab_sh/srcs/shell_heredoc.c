/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:24:20 by ringii            #+#    #+#             */
/*   Updated: 2022/12/15 17:21:50 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	wait_function(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status) == 1)
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) == 1)
		g_status = 128 + WTERMSIG(status);
}

int	exit_heredoc(t_redir *r, char *doc, int fd)
{
	doc = ft_strjoin_free(doc, "\n");
	write(fd, doc, ft_strlen(doc));
	close(fd);
	r->fd = open(HERE_DOC, O_RDONLY);
	free(doc);
	return (0);
}

int	ft_heredoc_loop(t_redir *r, int fd)
{
	char	*doc;
	char	*line;
	int		i;

	i = 0;
	doc = NULL;
	set_signal_heredoc(&interrupt_heredoc, SIGINT);
	set_signal_heredoc(&interrupt_heredoc, SIGQUIT);
	while (1)
	{
		write(1, "heredoc> ", 10);
		get_next_line(0, &line);
		if (strcmp(line, r->file_path) == 0)
			exit(exit_heredoc(r, doc, fd));
		if (i++ == 0)
			doc = ft_strdup(line);
		else
		{
			doc = ft_strjoin_free(doc, "\n");
			doc = ft_strjoin_free(doc, line);
		}
		free(line);
	}
	free(doc);
	exit (0);
}

int	heredoc(t_redir *r)
{
	pid_t	pid;
	int		fd;

	r->file_name = ft_strjoin(getcwd(NULL, 0), HERE_DOC);
	fd = open(r->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		errno = ECHILD;
		ft_error_msg("here_doc");
		return (-1);
	}
	else if (pid == 0)
		ft_heredoc_loop(r, fd);
	else
	{
		ignore_sig(SIGQUIT);
		ignore_sig(SIGINT);
		wait_function(pid);
		unlink(r->file_name);
		set_signals();
		set_sig();
	}
	close(fd);
	return (1);
}
