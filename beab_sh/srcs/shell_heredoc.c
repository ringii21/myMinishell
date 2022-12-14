/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:24:20 by ringii            #+#    #+#             */
/*   Updated: 2022/12/14 14:33:49 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	recursive(char **line, size_t index, int fd)
{
	char	buf;
	int		ret;

	ret = (int)read(fd, &buf, 1);
	if (ret == 1 && buf != '\n')
	{
		ret = recursive(line, index + 1, fd);
		if (ret != -1)
			(*line)[index] = buf;
	}
	else if (ret != -1)
	{
		*line = (char *)malloc(sizeof(char) * (index + 1));
		if (*line != NULL)
			(*line)[index] = '\0';
		else
			ret = -1;
	}
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	return (recursive(line, 0, fd));
}

/*int	heredoc(t_token *t, t_env *env)
{
 	char	*line;
	int		fd;

	fd = open(".heredoc_tmp", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (-1);
	while (1)
	{	
		line = NULL;
		write(1, "heredoc> ", 9);
		if (get_next_line(0, &line) < 0)
			return (-1);
		if (!ft_strncmp(t->file->file_path, line, ft_strlen(t->file->file_path) + 1))
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	return (1); 
	char	*doc;
	char	*line = NULL;
	int		i = 0;

	doc = NULL;
	//desactiver heredoc
	char *tmp = ft_strjoin(ft_path_finder(t, env, 0), "/.heredoc_tmp");
	t->file->file_name = tmp;
	int fd = open(tmp, O_CREAT | O_TRUNC | O_RDONLY | O_WRONLY, 0644);
	printf("fd [%d ]\n", fd);
	if (fd < 0)
		return (-1);
	while (1)
	{
		write(1, "heredoc > ", 10);
		get_next_line(0, &line); 
		if (strcmp(line, t->file->file_path) == 0)
		{
			doc = ft_strjoin_free(doc, "\n");
			write(fd, doc, ft_strlen(doc));
			close(fd);
			return (1);
		}
		else
		{
			if (i++ == 0)
				doc = strdup(line);
			else
			{
				doc = ft_strjoin_free(doc, "\n");
				doc = ft_strjoin_free(doc, line);
			}
		}
		free(line);
	}
	free(tmp);
	return (1);
}*/

void	wait_function(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status) == 1)
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) == 1)
		g_status = 128 + WTERMSIG(status);
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
		{
			if (i++ == 0)
				doc = strdup(line);
			else
			{
				doc = ft_strjoin_free(doc, "\n");
				doc = ft_strjoin_free(doc, line);
			}
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