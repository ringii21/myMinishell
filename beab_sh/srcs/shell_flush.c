/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_flush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:13:55 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/08 17:44:53 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_nodes(t_token *t)
{
	//int		i;
	t_redir	*tmp;

	//i = 0;
	if (t->av_copy)
		free(t->av_copy);
	t->av_copy = NULL;
	if (t->path)
		free(t->path);
	t->path = NULL;
	ft_free_stab(t->cmds_av);
	while (t->file)
	{
		tmp = t->file->next;
		if (t->file->path)
			free(t->file->path);
		free(t->file);
		t->file = tmp;
	}
}

void	ft_flush(t_token *t)
{
	t_token	*next;

	while (t && t->next)
		t = t->prev;
	while (t)
	{
		next = t->next;
		ft_free_nodes(t);
		t->cmd_ac = 0;
		free(t);
		t = next;
	}
}
