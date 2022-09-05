#include "libft.h"

static int recursive(char **line, size_t index, int fd)
{
    char buff;
    int ret;

    ret = read(fd, &buff, 1);
    if (ret == 1 && buff != '\n')
    {
        ret = recursive(line, index + 1, fd);
        if (ret != -1)
            (*line)[index] = buff;
    }
    else if (ret != -1)
    {
        *line = (char *)malloc(sizeof(char) * (index + 1));
        if (*line == NULL)
            return (-1);
        if (*line != NULL)
            (*line)[index] = '\0';
        else
            ret = -1;
    }
    return (ret);
}

int ft_gnl(int fd, char **line)
{
    return (recursive(line, 0, fd));
}
