#include "../inc/minishell.h"

int	ft_exit(t_env *env, char **cmds)
{
	(void)env;
	(void)cmds;

	exit(0);
	return (0);
}
