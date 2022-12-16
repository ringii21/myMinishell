/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_flush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:13:55 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/16 19:23:14 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_redir(t_redir *r, bool is_parent)
{
	t_redir	*tmp;

	while (r)
	{
		tmp = r->next;
		if (r->file_path)
			free(r->file_path);
		if (r->type == R_REDIR_IN && is_parent == true)
		{
			if (r->file_name != NULL)
				unlink(r->file_name);
		}
		if (r->file_name)
			free(r->file_name);
		free(r);
		r = tmp;
	}
}

void	ft_free_nodes(t_token *t)
{
	if (t->bin_path)
		free(t->bin_path);
	t->bin_path = NULL;
	if (t->cmds_av != NULL)
		ft_free_stab(t->cmds_av);
	if (t->file)
		free_redir(t->file, t->is_parent);
}

void	ft_flush(t_token *t)
{
	t_token	*next;

	if (t)
	{
		while (t->prev && t)
			t = t->prev;
		while (t)
		{
			next = t->next;
			ft_free_nodes(t);
			t->cmd_ac = 0;
	//		ft_close_fd(t);
			free(t);
			t = next;
		}
	}
}
