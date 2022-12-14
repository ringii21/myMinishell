/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:24:20 by ringii            #+#    #+#             */
/*   Updated: 2022/12/14 17:00:53 by abonard          ###   ########.fr       */
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

void ft_check_hereline(char *line, int i, char *doc)
{
	if (i++ == 0)
		doc = strdup(line);
	else
	{
		doc = ft_strjoin_free(doc, "\n");
		doc = ft_strjoin_free(doc, line);
	}
}

int	ft_heredoc_loop(t_token *t, int fd)
{
	char	*doc;
	char	*line;
	int		i = 0;

	doc = NULL;
	set_signal_heredoc(&interrupt_heredoc, SIGINT);
	set_signal_heredoc(&interrupt_heredoc, SIGQUIT);
	while (1)
	{
		write(1, "heredoc > ", 10);
		get_next_line(0, &line);
		if (strcmp(line, t->file->file_path) == 0)
		{
			doc = ft_strjoin_free(doc, "\n");
			write(fd, doc, ft_strlen(doc));
			close(fd);
			exit (0);
		}
		else
			ft_check_hereline(line, i, doc);
		free(line);
	}
	free(doc);
	exit (0);
}

int	heredoc(t_token *t, t_env *env)
{
	pid_t	pid;
	int		fd;

	t->file->file_name = ft_strjoin(ft_path_finder(t, env, 0), "/.heredoc.txt");
	fd = open(t->file->file_name, O_CREAT | O_TRUNC | O_RDONLY | O_WRONLY, 0644);
	if (fd < 0)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Minishell: Failed to fork processus\n", 2);
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