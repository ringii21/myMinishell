/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:16:05 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/13 12:49:32 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_pipes(t_token *t)
{
	t_redir	*tmp;

	ft_close_fd(t);
	tmp = t->file;
	while (tmp)
	{
		if (tmp->type == R_REDIR_IN)
		{
			close(tmp->file_pipe[0]);
			close(tmp->file_pipe[1]);
		}
		tmp = tmp->next;
	}
	if (t->prev && t->prev->is_pipe == 1)
		close(t->prev->bin_pipe[0]);
	if (!t->is_pipe)
		return ;
	close(t->bin_pipe[1]);
	if (t->next == NULL)
		close(t->bin_pipe[0]);
}

int	dup_pipes(t_token *t, int *is_pipe)
{
	if (t->is_pipe && dup2(t->bin_pipe[1], 1) < 0)
		return (0);
	if (t->prev && t->prev->is_pipe && dup2(t->prev->bin_pipe[0], 0) < 0)
		return (0);
	dup_redir(t);
	*is_pipe = 1;
	return (1);
}

int		process_exec(t_token *t, char **paths, char **env_cont)
{	
	int		ret;
	int		status;

	ret = 0;
	status = 0;
	t->pid = fork();
	if (t->pid == -1)
		ft_error(t->cmds_av[0]);
	else if (t->pid == 0)
	{
		if (execve(t->bin_path, t->cmds_av, env_cont) != -1)
		{
			ft_free_stab(env_cont);
			ft_free_stab(paths);
			ft_flush(t);
			ft_error(t->cmds_av[0]);
		}
	}
	else
	{
//		close_pipes(t);
		waitpid(-1, &status, 0);
		ret = WEXITSTATUS(status);
	}
	return (ret);
}

int	exec_bin(t_token *t, t_env *env)
{
	char	**paths;
	char	**env_cont;
	int		ret;

	ret = 0;
	paths = NULL;
	env_cont = NULL;
	shut_signals(t->pid);
	paths =  ft_split(get_cont("PATH", env), ':');
	t->bin_path = get_path(paths, t->cmds_av[0]);
	env_cont = ft_env_to_tab(env);
	ret = process_exec(t, paths, env_cont);
	return (ret);
}
