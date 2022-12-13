/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:24:20 by ringii            #+#    #+#             */
/*   Updated: 2022/12/13 17:24:10 by seozcan          ###   ########.fr       */
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

int	heredoc(t_token *t, t_env *env)
{
	char	*doc;
	char	*line;
	char 	*tmp;
	int		fd;
	int		i;

	i = -1;
	doc = NULL;
	tmp = ft_strjoin(ft_path_finder(t, env, 0), "/anais.txt");
	t->file->file_name = tmp;
	fd = open(tmp, O_CREAT | O_TRUNC | O_RDONLY | O_WRONLY, 0644);
	if (fd < 0)
		return (-1);
	while (1)
	{
		write(1, "heredoc > ", 10);
		get_next_line(0, &line);
		if (ft_strcmp(line, t->file->file_path) == 0)
		{
			ft_strjoin(doc, "\n");
			write(fd, doc, ft_strlen(doc));
			return (1);
		}
		else
		{
			if (i++ == 0)
				doc = ft_strdup(line);
			else
			{

				doc = ft_strjoin(doc, "\n");
				doc = ft_strjoin(doc, line);
			}
		}
		free(line);
	}
	free(tmp);
	return (1);
}