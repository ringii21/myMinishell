/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:19:04 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/14 22:58:49 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_binpath(t_main *m, char *bin, char **sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		bin = ft_strjoin(sep[i], "/");
		bin = ft_strjoin_free(bin, m->t->cmds_av[0]);
		if (access(bin, X_OK) == 0)
			return (bin);
		free(bin);
		i++;
	}
	return (NULL);
}

int	get_path(t_token *t, t_main *m)
{
	char *bin;
	char **sep_path;

	bin = NULL;
	t->bin_path = ft_strdup(get_cont("PATH", m->env));
	if (t->bin_path == NULL)
		return (1);
	if (t->cmds_av[0][0] != '/' && ft_strncmp(t->cmds_av[0], "./", 2) != 0)
	{
		sep_path = ft_split(t->bin_path, ':');
		bin = get_binpath(m, bin, sep_path);
		if (bin == NULL)
		{
			ft_error_msg(t->cmds_av[0]);
			// Status code ici
			return ;
		}
		free(t->bin_path);
		t->bin_path = bin;
		ft_free_stab(sep_path);
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
		t->bin_path = ft_strdup("\0");
	else if (ft_strchr(t->cmds_av[0], '/') != 0)
		t->bin_path = ft_strdup(t->cmds_av[0]);
	else
		if (get_path(t, m) == 127)
			return (127);
	return (res);
}
