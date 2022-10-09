/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:26 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/08 22:30:17 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_path_finder(t_main *m, bool is_forked)
{
	char	*path;

	m->o.cmd_flags = ft_split(m->o.cmds[0], ' ');
	m->o.cmd_ac = ft_tablen(m->o.cmd_flags);
	if (m->o.cmd_ac < 2)
	{
		path = get_cont("HOME", m->env);
		if (path == NULL && is_forked)
			ft_putstr_fd("HOME not set\n", 2);
	}
	else
	{
		if (m->o.cmd_flags[1][0] == '-' && m->o.cmd_flags[1][1] == '\0')
		{
			path = get_cont("OLDPWD", m->env);
			if (path == NULL && is_forked)
				ft_putstr_fd("OLDPWD not set\n", 2);
			else if (is_forked)
				printf("%s\n", path);
		}
		else
			path = m->o.cmd_flags[1];
	}
	return (path);
}

void	ft_cd_fail(char *path, int ret, bool is_forked)
{
	if (!is_forked)
		return ;
	if (ret == ENOTDIR)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	else if (ret == ENOENT)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (ret == EACCES)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

int	ft_cd(t_main *m, bool is_forked)
{
	char	*path;
	int		ret;
	char	*oldpath;

	path = ft_path_finder(m, is_forked);
	if (path == NULL)
		return (4);
	oldpath = getcwd(NULL, 0);
	ret = chdir(path);
	if (ret != 0)
		ft_cd_fail(path, errno, is_forked);
	else
	{
		if (oldpath)
			ft_create_o_replace("OLDPWD", oldpath, m->env);
		path = getcwd(NULL, 0);
		if (path == NULL)
			return (4);
		ft_create_o_replace("PWD", path, m->env);
		free(path);
	}
	free(oldpath);
	ft_free_stab(m->o.cmd_flags);
	return (ret);
}
