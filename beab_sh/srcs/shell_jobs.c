/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:34:43 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/08 17:00:39 by seozcan          ###   ########.fr       */
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

char *get_binpath(t_main *m, char *bin, char **sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		bin = ft_strjoin(sep[i], "/");
		bin = ft_strjoin(bin, m->t->cmds_av[0]);
		if (access(bin, X_OK) == 0)
			return (bin);
		free(bin);
		i++;
	}
	return (NULL);
}

void	get_path(t_token *t, t_main *m)
{
	char *bin;
	char **sep_path;

	bin = NULL;
	t->path = ft_strdup(get_cont("PATH", m->env));
	if (t->path == NULL)
		return ;
	if (t->cmds_av[0][0] != '/' && ft_strncmp(t->cmds_av[0], "./", 2) != 0)
	{
		sep_path = ft_split(t->path, ':');
		bin = get_binpath(m, bin, sep_path);
		if (bin == NULL)
		{
			ft_putstr_fd("command not found\n", 2);
			return ;
		}
		free(t->cmds_av[0]);
		t->cmds_av[0] = bin;
		ft_free_stab(sep_path);
	}
	else
		free(m->t->path);
	
}

/* void	execute(t_main *m)
{
	m->t.cmd_flags = ft_split(m->t.cmds[m->t.index], ' ');
	m->t.bin_path = get_cmd(m->t.paths, m->t.cmd_flags[0]);
	m->t.envtab = ft_env_to_tab(m->env);
	if (execve(m->t.bin_path, m->t.cmd_flags, m->t.envtab) != -1)
	{
		ft_free_child(&m->t);
		ft_free_parent(&m->t);
		ft_error();
	}
} */

// serach for status code for all the builtin created
 int	exec_builtin(t_token *t, t_env *env, bool is_forked)
{
	int	ret;

	ret = -1;

	if (ft_strcmp("env", t->cmds_av[0]) == 0)
		ret = ft_env(env);
		
	if (ft_strcmp("exit", t->cmds_av[0]) == 0)
		ret = ft_exit(t, is_forked);
		
	if (ft_strcmp("pwd", t->cmds_av[0]) == 0)
		ret = ft_pwd(env);

	if (ft_strcmp("cd", t->cmds_av[0]) == 0)
		ret = ft_cd(t, env, is_forked);

	if (ft_strcmp("echo", t->cmds_av[0]) == 0)
		ret = ft_echo(t);
		
	if (ft_strcmp("export", t->cmds_av[0]) == 0)
		ret = ft_export(t, env, is_forked);
		
	if (ft_strcmp("unset", t->cmds_av[0]) == 0)
		ret = ft_unset(t, env, is_forked);
	return (ret);
}
	// serach for status code for all the builtin created

int	which_path(t_main *m, t_token *t)
{
	int res;

	res = 0;
	if (t->cmds_av == NULL)
		return (0);
	if (is_builtin(t->cmds_av) == 1)
		t->path = ft_strdup("\0");
	else if (ft_strchr(t->cmds_av[0], '/') != 0)
		t->path = ft_strdup(t->cmds_av[0]);
	else
		get_path(t, m);
	return (res);
}

int	ft_redir(t_token *t, t_env *env)
{
	if (ft_input(t, env) == 1)
		return (1);
	if (ft_output(t) == 1)
		return (1);
	return (0);
}

int	ft_cmds_handler(t_token *t, t_env *env, bool builtin)
{
	int		res;
	res = 0;
	t->is_pipe_o = 0;
 	if (t->is_pipe == 1 || (t->prev && t->prev->is_pipe == 1))
	{
		t->is_pipe_o = 1;
		if (pipe(t->pipe_fd))
			return (-1);
	}
	if (ft_redir(t, env))
		return (4);
	t->pid = fork();
	shut_signals(t->pid);
	if (t->pid == -1)
		return (1); // Erreur fork
	if (t->pid == 0)
		child_process(t, env, builtin);
	ft_close_pipe(t);
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

int	ft_hold_exec(t_token *t, t_env *env)
{
	int	res;
	int status;
	
	res = 130;
	while(t)
	{
		status = 0;
		waitpid(t->pid, &status, 0);
		if (WIFEXITED(status))
			res = WEXITSTATUS(status);
		if (!t->path || ft_strcmp(t->cmds_av[0], "exit") == 0)// && t->path[0] == '\0')
			exec_builtin(t, env, false); 
		t = t->next;
	}
	set_signals();
	return (res);
}

int	job(t_main *m)
{
	int		res;
	t_token *list_cmd;
	
	list_cmd = m->t;
	res = 0;
	while (m->t)
	{
		res = which_path(m, m->t);
		if (res != 0)
			return (-1); // gere les erreurs
		else
			res = ft_cmds_handler(m->t, m->env, m->t->path && m->t->path[0] == '\0');
		m->t = m->t->next;
	}
	m->t = list_cmd;
	res = ft_hold_exec(list_cmd, m->env);
	return (res);
}