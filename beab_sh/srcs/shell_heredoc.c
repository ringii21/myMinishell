/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:24:20 by ringii            #+#    #+#             */
/*   Updated: 2022/12/16 22:21:29 by seozcan          ###   ########.fr       */
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
	free(doc);
	r->fd = open(r->file_name, O_RDONLY);
	return (0);
}

int	ft_heredoc_loop(t_token *t, t_env *env, t_redir *r, int fd)
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
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (strcmp(line, r->file_path) == 0)
			return (ft_mini_exit(exit_heredoc(r, doc, fd), t, env));
		if (i++ == 0)
			doc = ft_strdup(line);
		else
			doc = ft_strjoin_free(doc, line);
		doc = ft_strjoin_free(doc, "\n");
		free(line);
	}
	free(doc);
	return (ft_mini_exit(0, t, env));
}

int	ft_open_heredoc(t_redir *r)
{
	char	*cwd;
	char	*nb;

	cwd = getcwd(NULL, 0);
	r->file_name = ft_strjoin(cwd, HERE_DOC);
	nb = ft_itoa(r->nb_heredoc);
	r->file_name = ft_strjoin_free(r->file_name, nb);
	free(nb);
	free(cwd);
	return (open(r->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644));
}

int	heredoc(t_token *t, t_redir *r, t_env *env)
{
	pid_t	pid;
	int		fd;

	fd = ft_open_heredoc(r);
	if (fd < 0)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		errno = ECHILD;
		return (ft_error_msg(1, HERE_DOC));
	}
	else if (pid == 0)
	{
		t->is_parent = false;
		ft_heredoc_loop(t, env, r, fd);
	}
	ignore_sig(SIGQUIT);
	ignore_sig(SIGINT);
	t->is_parent = true;
	wait_function(pid);
	set_signals();
	set_sig();
	close(fd);
	return (1);
}
