/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:10:36 by root              #+#    #+#             */
/*   Updated: 2022/12/08 15:16:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_redir(char *is_out, char *is_in)
{
	while(*is_in)
	{
		if(!*is_out)
			return(0);
		if (*is_out != *is_in)
			return (0);
		++is_out;
		++is_in;
	}
	return (1);
}

int	redir_manager(t_parsing *parser, char *str)
{
	if (str[parser->i] == '<' || str[parser->i] == '>')
	{
		fill_args(&parser->read, &parser->type, parser->cursor, &parser->is_quote);
		if (parser->type != DEFAULT)
			return (3);
		if (find_redir(str + parser->i, "<<") && ++parser->i)
			parser->type = R_REDIR_IN;
		else if (find_redir(str + parser->i, ">>") && ++parser->i)
			parser->type = R_REDIR_OUT;
		else if (find_redir(str + parser->i, ">") && !find_redir(str + parser->i, "<"))
			parser->type = REDIR_OUT;
		else if (find_redir(str + parser->i, "<") && !find_redir(str + parser->i, ">"))
			parser->type = REDIR_IN;
		else
			return (3);
		parser->i++;
		return (1);
	}
	return (0);
}