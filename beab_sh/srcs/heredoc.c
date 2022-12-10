# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
#include <fcntl.h>

static int	recursive(char **line, size_t index, int fd)
{
	char	buf;
	int		ret;

	ret = read(fd, &buf, 1);
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
	len_s1 = strlen(s1);
	len_s2 = strlen(s2);
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
		res[len_s1 + i] = s2[i];
		i++;
	}
	return (res);
}

int	ft_heredoc(void)
{
	char	*doc;
	char	*line;
	int fd;
	int i = -1;

	fd = open("/home/wac/Desktop/heredoc/file", O_RDWR | O_CREAT | O_TRUNC);
	if (fd < 0)
		return (-1);
	while (1)
	{
		write(1, "heredoc >", 10);
		get_next_line(0, &line);
		if (strcmp(line, "FIN") == 0)
		{
			printf("je passe ici %d  fois\n", i);
			ft_strjoin(doc, "\n");
			write(fd, doc, strlen(doc));
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
	return (1);
}

int main(void)
{
	ft_heredoc();
	return (0);
}