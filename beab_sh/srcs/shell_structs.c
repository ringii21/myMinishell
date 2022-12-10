/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ringii <ringii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:47:26 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/10 14:08:39 by ringii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	fill_redir(t_token *t, char *str, t_type type, bool *is_quote)
{
	t_redir	*new;
	t_redir	*tmp;

	new = xmalloc(sizeof(t_redir));
	new->path = str;
	new->type = type;
	new->next = NULL;
	if (is_quote)
		new->is_quote = *is_quote;
	else
		new->is_quote = false;
	if (!t->file)
		t->file = new;
	else
	{
		tmp = t->file;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	fill_args(char **str, t_type *type, t_token *t, bool *is_quote)
{
	if (*str && **str)
	{
		if (!type || *type == DEFAULT)
			split_args(t, *str);
		else
			fill_redir(t, *str, *type, is_quote);
		if (is_quote)
			*is_quote = false;
		*str = NULL;
		if (type)
			*type = DEFAULT;
	}	
}
