/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_flush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:13:55 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/08 16:16:13 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_free_nodes(t_token *o)
{
	int	i;
	t_redir *tmp;

	i = 0;
	if (o->av_copy)
		free(o->av_copy);
	o->av_copy = NULL;
	if (o->path)
		free(o->path);
	o->path = NULL;
	ft_free_stab(o->cmds_av);
	while (o->file)
	{
		tmp = o->file->next;
		if (o->file->path)
			free(o->file->path);
		free(o->file);
		o->file = tmp;
	}
}

void ft_flush(t_token *o)
{
	t_token	*next;
	while (o && o->next)
		o = o->prev;
	while (o)
	{
		next = o->next;
		ft_free_nodes(o);
		o->cmd_ac = 0;
		free(o);
		o = next;
	}
}