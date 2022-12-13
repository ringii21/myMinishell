/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:19:04 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/11 18:34:15 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_path(char **paths, char *cmd)
{
	char	*ret;
	int		i;

	i = 0;
	if (access(cmd, 0) == 0)
		return (cmd);
	while (paths[i])
	{
		ret = NULL;
		ret = ft_strjoin(paths[i], "/");
		ret = ft_strjoin(ret, cmd);
		if (access(ret, X_OK) == 0)
			return (ret);
		free(ret);
		i++;
	}
	perror(cmd);
	return (NULL);
}
