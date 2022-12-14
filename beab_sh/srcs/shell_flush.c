/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_flush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:13:55 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/14 16:46:50 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_free_nodes(t_token *t)
{
	t_redir *tmp;

	if (t->av_copy)
		free(t->av_copy);
	t->av_copy = NULL;
	if (t->bin_path)
		free(t->bin_path);
	t->bin_path = NULL;
	if (t->cmds_av != NULL)
		ft_free_stab(t->cmds_av);
	while (t->file)
	{
		tmp = t->file->next;
		if (t->file->file_name)
			free(t->file->file_name);
		if (t->file->file_path)
			free(t->file->file_path);
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
