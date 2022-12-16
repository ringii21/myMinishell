/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:10:36 by root              #+#    #+#             */
/*   Updated: 2022/12/16 23:59:20 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_redir(char *is_out, char *is_in)
{
	while (*is_in)
	{
		if (!*is_out)
			return (0);
		if (*is_out != *is_in)
			return (0);
		++is_out;
		++is_in;
	}
	return (1);
}

int	redir_manager(t_main *m, t_parse *p, char *str)
{
	if (str[p->i] == '<' || str[p->i] == '>')
	{
		fill_args(&p->read, &p->type, m->cursor, &p->is_quote);
		if (p->type != DEFAULT)
			return (3);
		if (find_redir(str + p->i, "<<") && ++p->i)
			p->type = R_REDIR_IN;
		else if (find_redir(str + p->i, ">>") && ++p->i)
			p->type = R_REDIR_OUT;
		else if (find_redir(str + p->i, ">") && !find_redir(str + p->i, "<"))
			p->type = REDIR_OUT;
		else if (find_redir(str + p->i, "<") && !find_redir(str + p->i, ">"))
			p->type = REDIR_IN;
		else
			return (3);
		p->i++;
		return (1);
	}
	return (0);
}
