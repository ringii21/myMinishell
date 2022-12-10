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

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len_s1;
	unsigned int	len_s2;
	int				i;
	char			*res;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = (unsigned int)ft_strlen(s1);
	len_s2 = (unsigned int)ft_strlen(s2);
	res = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (res == NULL)
		return (NULL);
	res[len_s1 + len_s2] = '\0';
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	i = 0;
	while (s2[i])
	{
		res[len_s1 + (unsigned int)i] = s2[i];
		i++;
	}
	return (res);
}

int	heredoc(t_token *t, t_env *env)
{
	char	*doc;
	char	*line;
	int		fd;
	int		i = -1;

	doc = NULL;
	char *tmp = ft_strjoin(ft_path_finder(t, env, 0), "/anais.txt");
	fd = open(tmp, O_CREAT | O_TRUNC | O_RDONLY, 0644);
	printf("fd [%d ]\n", fd);
	if (fd < 0)
		return (-1);
	while (1)
	{
		write(1, "heredoc >", 10);
		get_next_line(0, &line);
		if (strcmp(line, t->file->path) == 0)
		{
			ft_strjoin(doc, "\n");
			write(fd, doc, ft_strlen(doc));
			return (1);
		}
		else
		{
			if (i++ == 0)
				doc = strdup(line);
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