/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:42:51 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/29 04:35:10 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*ret;
	int		i;

	i = 0;
	if (access(cmd, 0) == 0)
		return (cmd);
	else
	{
		while (paths[i])
		{
			tmp = ft_strjoin(paths[i], "/");
			ret = ft_strjoin(tmp, cmd);
			free(tmp);
			if (access(ret, X_OK) == 0)
				return (ret);
			free(ret);
			i++;
		}
		ft_putstr_fd("command not found\n", 2);
		ft_error();
	}
	return (NULL);
}

t_operator	identify_operator(t_main *m)
{
	t_operator	i;

	i = 0;
	while (m->operators[(int)i])
	{
		if (!ft_strncmp(m->operators[(int)i], m->buf, ft_strlen(m->buf)))
			return (i);
		i++;
	}
	return (O_CMD);
}

void	control_operator(t_token *content, t_main *m)
{	
	t_operator	control_op;

	control_op = identify_operator(m);
	content->id = control_op;
	if (control_op <= O_AND)
	{
		content->is_piped = 1;
		m->pipe_ac++;
	}
	else if (control_op >= O_STDIN_REDIR && control_op <= O_APPEN)
		content->is_redir = 1;
}
