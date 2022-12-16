/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:47:26 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/16 19:12:38 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	return_value_nb_heredoc(t_token *t)
{
	t_token	*tmp;
	t_redir	*tmp2;
	int		i;

	i = 0;
	tmp = t;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		tmp2 = tmp->file;
		while (tmp2)
		{
			i++;
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (i);
}

void	fill_redir(t_token *t, char *str, t_type type, bool *is_quote)
{
	t_redir	*new;
	t_redir	*tmp;


	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->file_path = str;
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
	new->nb_heredoc = return_value_nb_heredoc(t);
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
