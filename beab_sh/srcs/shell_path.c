/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:19:04 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/16 19:00:32 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_binpath(t_main *m, char **sep)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (sep[i])
	{
		tmp = ft_strjoin(sep[i], "/");
		tmp = ft_strjoin_free(tmp, m->t->cmds_av[0]);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

int	get_path(t_token *t, t_main *m)
{
	char	**sep_path;

	t->bin_path = ft_strdup(get_cont("PATH", m->env));
	if (t->bin_path == NULL)
		return (1);
	if (t->cmds_av[0][0] != '/' && ft_strncmp(t->cmds_av[0], "./", 2) != 0)
	{
		sep_path = ft_split(t->bin_path, ':');
		free(t->bin_path);
		t->bin_path = get_binpath(m, sep_path);
		ft_free_stab(sep_path);
		if (t->bin_path == NULL)
			return (return_error_cmd_nf(t));
	}
	else
		free(m->t->bin_path);
	return (1);
}

int	which_path(t_main *m, t_token *t)
{
	int	res;

	res = 0;
	if (t->cmds_av == NULL)
		return (0);
	if (is_builtin(t->cmds_av) == 1)
	{
		if (t->bin_path)
			free(t->bin_path);
		t->bin_path = NULL;
		t->bin_path = ft_strdup("\0");
	}
	else if (ft_strchr(t->cmds_av[0], '/') != 0)
		t->bin_path = ft_strdup(t->cmds_av[0]);
	else
		if (get_path(t, m) == 127)
			return (127);
	return (res);
}
