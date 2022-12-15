/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:24:20 by ringii            #+#    #+#             */
/*   Updated: 2022/12/15 14:20:29 by abonard          ###   ########.fr       */
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

int	exit_heredoc(char *doc, int fd)
{
	doc = ft_strjoin_free(doc, "\n");
	write(fd, doc, ft_strlen(doc));
	close(fd);
	free(doc);
	return (0);
}

int	ft_heredoc_loop(t_token *t, int fd)
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
		if (strcmp(line, t->file->file_path) == 0)
			exit(exit_heredoc(doc, fd));
		if (i++ == 0)
			doc = strdup(line);
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

int	heredoc(t_token *t, t_env *env)
{
	pid_t	pid;
	int		fd;

	t->file->file_name = ft_strjoin(ft_path_finder(t, env, 0), HERE_DOC);
	fd = open(t->file->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		errno = ECHILD;
		ft_error_msg(t->cmds_av[0]);
		return (-1);
	}
	else if (pid == 0)
		ft_heredoc_loop(t, fd);
	else
	{
		ignore_sig(SIGQUIT);
		ignore_sig(SIGINT);
		wait_function(pid);
		set_signals();
		set_sig();
	}
	close(fd);
	return (1);
}