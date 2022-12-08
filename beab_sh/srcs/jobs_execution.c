/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wac <wac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:34:43 by seozcan           #+#    #+#             */
/*   Updated: 2022/11/17 00:16:03 by wac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* static char	*get_cmd(char **paths, char *cmd)
{
 	char	*tmp;
	char	*ret;

	if (access(cmd, 0) == 0)
		return (cmd);
	else
	{
		while (*paths)
		{
			tmp = ft_strjoin(*paths, "/");
			ret = ft_strjoin(tmp, cmd);
			free(tmp);
			if (access(ret, X_OK) == 0)
				return (ret);
			free(ret);
			paths++;
		}
		ft_putstr_fd("command not found\n", 2);
	}
	return (NULL); 
} */

char *ft_mr_bin(t_main *m, char *bin, char **sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		bin = ft_strjoin(sep[i], "/");
		bin = ft_strjoin(bin, m->o->cmds_av[0]);
		if (access(bin, X_OK) == 0)
			return (bin);
		free(bin);
		i++;
	}
	return (NULL);
}

void	ft_get_path(t_obj *o, t_main *m)
{
	char *bin;
	char **sep_path;

	bin = NULL;
	o->path = ft_strdup(get_cont("PATH", m->env));
	if (o->path == NULL)
		return ;
	if (o->cmds_av[0][0] != '/' && ft_strncmp(o->cmds_av[0], "./", 2) != 0)
	{
		sep_path = ft_split(o->path, ':');
		bin = ft_mr_bin(m, bin, sep_path);
		if (bin == NULL)
		{
			ft_putstr_fd("command not found\n", 2);
			return ;
		}
		free(o->cmds_av[0]);
		o->cmds_av[0] = bin;
		ft_free_stab(sep_path);
	}
	else
		free(m->o->path);
	
}

/* void	execute(t_main *m)
{
	m->o.cmd_flags = ft_split(m->o.cmds[m->o.index], ' ');
	m->o.bin_path = get_cmd(m->o.paths, m->o.cmd_flags[0]);
	m->o.envtab = ft_env_to_tab(m->env);
	if (execve(m->o.bin_path, m->o.cmd_flags, m->o.envtab) != -1)
	{
		ft_free_child(&m->o);
		ft_free_parent(&m->o);
		ft_error();
	}
} */

// serach for status code for all the builtin created
 int	exec_builtin(t_obj *o, t_env *env, bool is_forked)
{
	int	ret;

	ret = -1;
/* 	printf("%s\n", o->cmds_av[0]);
	exit(1); */
	if (ft_strcmp("env", o->cmds_av[0]) == 0)
		ret = ft_env(env);
		
	if (ft_strcmp("exit", o->cmds_av[0]) == 0)
		ret = ft_exit(o, is_forked);
		
	if (ft_strcmp("pwd", o->cmds_av[0]) == 0)
		ret = ft_pwd(env);

	if (ft_strcmp("cd", o->cmds_av[0]) == 0)
		ret = ft_cd(o, env, is_forked);

	if (ft_strcmp("echo", o->cmds_av[0]) == 0)
		ret = ft_echo(o);
		
	if (ft_strcmp("export", o->cmds_av[0]) == 0)
		ret = ft_export(o, env, is_forked);
		
	if (ft_strcmp("unset", o->cmds_av[0]) == 0)
		ret = ft_unset(o, env, is_forked);
	return (ret);
}
	// serach for status code for all the builtin created

int	which_path(t_main *m, t_obj *o)
{
	int res;

	res = 0;
	if (o->cmds_av == NULL)
		return (0);
	if (is_builtin(o->cmds_av) == 1)
		o->path = ft_strdup("\0");
	else if (ft_strchr(o->cmds_av[0], '/') != 0)
		o->path = ft_strdup(o->cmds_av[0]);
	else
		ft_get_path(o, m);
	return (res);
}

int	ft_redir(t_obj *o, t_env *env)
{
	if (ft_input(o, env) == 1)
		return (1);
	if (ft_output(o) == 1)
		return (1);
	return (0);
}


int	ft_cmds_handler(t_obj *o, t_env *env, bool builtin)
{
	int		res;
	res = 0;
	o->is_pipe_o = 0;
 	if (o->is_pipe == 1 || (o->prev && o->prev->is_pipe == 1))
	{
		o->is_pipe_o = 1;
		if (pipe(o->pipe_fd))
			return (-1);
	}
	if (ft_redir(o, env))
		return (4);
	o->pid = fork();
	shut_signals(o->pid);
	if (o->pid == -1)
		return (1); // Erreur fork
	if (o->pid == 0)
		ft_child_play(o, env, builtin);
	ft_close_pipe(o);
	return (res);
}

char	*last_error(bool set, int err)
{
	static char	*value;

	if (set)
	{
		if (value)
			free(value);
		value = ft_itoa(err);
	}
	else if (!value)
		value = ft_strdup("0");
	return (value);
}

int	ft_hold_exec(t_obj *o, t_env *env)
{
	int	res;
	int status;
	
	res = 130;
	while(o)
	{
		status = 0;
		waitpid(o->pid, &status, 0);
		if (WIFEXITED(status))
			res = WEXITSTATUS(status);
		if (!o->path || ft_strcmp(o->cmds_av[0], "exit") == 0)// && o->path[0] == '\0')
			exec_builtin(o, env, false); 
		o = o->next;
	}
	set_signals();
	return (res);
}

int	job(t_main *m)
{
	int	res;
	t_obj *list_cmd;
	
	list_cmd = m->o;
	res = 0;

	while (m->o)
	{
		res = which_path(m, m->o);
		if (res != 0)
			return (-1); // gere les erreurs
		else
			res = ft_cmds_handler(m->o, m->env, m->o->path && m->o->path[0] == '\0');
		m->o = m->o->next;
	}
	m->o = list_cmd;
	res = ft_hold_exec(list_cmd, m->env);
	return (res);
}