#include "../inc/minishell.h"

int	ft_buildin_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (tmp == NULL)
		return (1);
	while (tmp->next != NULL)
	{
		printf("%s\n", tmp->total);
		tmp = tmp->next;
	}
	return (0);
}
