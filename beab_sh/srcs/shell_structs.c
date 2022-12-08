/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:47:26 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/08 15:47:51 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	fill_redir(t_token *parser, char *str, enum redir_type type, bool *is_quote)
{
	t_redir *new;
	t_redir *tmp;

	new = xmalloc(sizeof(t_redir));
	if (new == NULL)
		return ;
	new->path = str;
	new->type = type;
	new->next = NULL;
	if (is_quote)
		new->is_quote = *is_quote;
	else
		new->is_quote = false;
	if (!parser->file)
		parser->file = new;
	else
	{
		tmp = parser->file;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void  fill_args(char **str, enum redir_type *type, t_token *parser, bool *is_quote)
{
	if (*str && **str)
	{
		if (!type || *type == DEFAULT)
			split_args(parser, *str);
		else
			fill_redir(parser, *str, *type, is_quote);
		if (is_quote)
			*is_quote = false;
		*str = NULL;
		if (type)
			*type = DEFAULT;
	}	
}
