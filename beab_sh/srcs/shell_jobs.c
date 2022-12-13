/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:34:43 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/13 12:49:20 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_hold_exec(t_main *m, t_token *t/* , t_env *env */)
{
	int	res;
	int	status;

	res = 130;
	status = 0;
	while (t)
	{
		waitpid(-1, &status, 0);
		res = WEXITSTATUS(status);
		if (ft_strcmp(t->cmds_av[0], "exit") == 0)
			/*  || ft_strcmp(t->cmds_av[0], "cd") == 0
			|| ft_strcmp(t->cmds_av[0], "export") == 0
			|| ft_strcmp(t->cmds_av[0], "unset") == 0 )
			exec_builtin(t, env, false);  */
			ft_exit(m, t);
		t = t->next;
	}
	set_signals();
	return (res);
}

int	assign_jobs(t_main *m, t_token *t, t_env *env)
{	
	if (t->is_pipe == 1 || (t->prev && t->prev->is_pipe == 1))
	{
		t->is_pipe_open = 1;
		if (pipe(t->bin_pipe) == -1)
			return (-1);
	}
	if (ft_redir(t, env))
		return (4);
	if (!dup_pipes(t, &(t->is_pipe_open)))
		exit(EXIT_FAILURE);
	if (t->is_pipe)
		close(t->bin_pipe[0]);
	if (t->cmds_av && ft_strcmp(t->cmds_av[0], "exit") == 0 && !t->is_pipe)
		ft_exit(m, t);
	else if (t->cmds_av && is_builtin(t->cmds_av))
		exec_builtin(t, env, false);
	else if (t->cmds_av)
		exec_bin(t, env);
	close_pipes(t);

	return (0);
}

int	job(t_main *m)
{
	t_token	*tmp;

	tmp = m->t;
	while (tmp)
	{
		if (assign_jobs(m, tmp, m->env) == -1)
			return (-1);
		tmp = tmp->next;
	}
//	return (ft_hold_exec(m, m->t, m->env ));
	return (m->ret);
}
