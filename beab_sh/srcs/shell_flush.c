/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_flush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:13:55 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/14 22:39:43 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_redir(t_redir *r)
{
	t_redir *tmp;

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

void ft_free_nodes(t_token *t)
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
