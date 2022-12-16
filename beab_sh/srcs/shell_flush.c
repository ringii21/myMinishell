/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_flush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:13:55 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/17 00:34:50 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_redir(t_redir *r, bool is_parent)
{
	t_redir	*tmp;

	(void)is_parent;
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

void	free_tokens(t_token *t)
{
	if (t->bin_path)
		free(t->bin_path);
	t->bin_path = NULL;
	if (t->cmds_av != NULL)
		ft_free_stab(t->cmds_av);
	if (t->file)
		free_redir(t->file, t->is_parent);
}

void	free_parser(t_parse *p)
{
	if (p->read)
		free(p->read);
	free(p);
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
			free_tokens(t);
			t->cmd_ac = 0;
			free(t);
			t = next;
		}
	}
}
