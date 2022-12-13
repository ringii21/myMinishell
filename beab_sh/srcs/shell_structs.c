/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:47:26 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/13 15:45:20 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	fill_redir(t_token *t, char *str, t_type type, bool *is_quote)
{
	t_redir	*new;
	t_redir	*tmp;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return ;
	new->file_path = ft_strdup(str);
	new->file_name = NULL;
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
