/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_flush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:13:55 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/11 13:44:56 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_redir(t_redir *r)
{
	t_redir	*tmp;

	while (r)
	{
		tmp = r->next;
		if (r->file_path)
			free(r->file_path);
		free(r);
		r = tmp;
	}
}

void	free_token(t_token *t)
{
	if (t->bin_path)
		free(t->bin_path);
	ft_free_stab(t->cmds_av);
}

void	ft_flush(t_token *t)
{
	t_token	*next;

	while (t && t->next)
		t = t->prev;
	while (t)
	{
		next = t->next;
		free_token(t);
		if (t->file)
			free_redir(t->file);
		t->cmd_ac = 0;
		free(t);
		t = next;
	}
}
