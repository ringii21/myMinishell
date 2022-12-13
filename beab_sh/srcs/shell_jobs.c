/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:34:43 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/13 15:11:34 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_builtin(t_token *t, t_env *env, bool is_forked)
{
	int	ret;

	ret = -1;
	if (ft_strcmplen("env", t->cmds_av[0]) == 0)
		ret = ft_env(env);
	if (ft_strcmplen("exit", t->cmds_av[0]) == 0)
		ret = ft_exit(t, is_forked);
	if (ft_strcmplen("pwd", t->cmds_av[0]) == 0)
		ret = ft_pwd(env);
	if (ft_strcmplen("cd", t->cmds_av[0]) == 0)
		ret = ft_cd(t, env, is_forked);
	if (ft_strcmplen("echo", t->cmds_av[0]) == 0)
		ret = ft_echo(t);
	if (ft_strcmplen("export", t->cmds_av[0]) == 0)
		ret = ft_export(t, env, is_forked);
	if (ft_strcmplen("unset", t->cmds_av[0]) == 0)
		ret = ft_unset(t, env, is_forked);
	return (ret);
}

int	ft_hold_exec(t_token *t, t_env *env)
{
	int	res;
	int	status;

	res = 130;
	while (t)
	{
		status = 0;
		waitpid(t->pid, &status, 0);
		if (WIFEXITED(status))
			res = WEXITSTATUS(status);
		if (t->bin_path != NULL && (ft_strcmplen(t->cmds_av[0], "exit") == 0 
			|| ft_strcmplen(t->cmds_av[0], "export") == 0 || (ft_strcmplen(t->cmds_av[0], "cd") == 0) 
				|| (ft_strcmp(t->cmds_av[0], "unset") == 0)))
					exec_builtin(t, env, false);
		t = t->next;
	}
	set_signals();
	return (res);
}

int	assign_jobs(t_token *t, t_env *env, bool builtin)
{
	int	res;

	res = 0;
	t->is_pipe_open = 0;
	if (t->is_pipe == 1 || (t->prev && t->prev->is_pipe == 1))
	{
		t->is_pipe_open = 1;
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
	close_pipes(t);
	return (res);
}

int	job(t_main *m)
{
	int		res;
	t_token	*list_cmd;

	list_cmd = m->t;
	res = 0;
	while (m->t)
	{
		res = which_path(m, m->t);
		if (res != 0)
			return (-1); // gere les erreurs
		else
		{
			res = assign_jobs(m->t, m->env, m->t->bin_path
					&& m->t->bin_path[0] == '\0');
		}
		m->t = m->t->next;
	}
	m->t = list_cmd;
	res = ft_hold_exec(list_cmd, m->env);
	return (res);
}
