/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_flush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:13:55 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/15 14:59:33 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* void	ft_free_nodes(t_token *o)
{
	t_redir	*tmp;

	if (o->bin_path)
		free(o->bin_path);
	o->bin_path = NULL;
	if (o->cmds_av != NULL)
		ft_free_stab(o->cmds_av);
	while (o->file)
	{
		tmp = o->file->next;
		if (o->file->file_name)
			free(o->file->file_name);
		if (o->file->file_path)
			free(o->file->file_path);
		free(o->file);
		o->file = tmp;
	}
}

void	ft_flush(t_token *o)
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
} */

void	free_redir(t_redir *r)
{
	t_redir	*tmp;

	while (r)
	{
		tmp = r;
		if (r->file_name)
			free(r->file_name);
		if (r->file_path)
			free(r->file_path);
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
		free_redir(t->file);
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
