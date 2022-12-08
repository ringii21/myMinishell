/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:41:11 by root              #+#    #+#             */
/*   Updated: 2022/12/08 15:48:59 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void next_token(t_token **cursor, int is_pipe)
{
	t_token *tmp;

	tmp = *cursor;
	if (is_pipe)
		(*cursor)->is_pipe = is_pipe;
	(*cursor)->next = init_token();
	*cursor = (*cursor)->next;
	(*cursor)->prev = tmp;
}

int	quote_manager(t_parsing *parser, char *str, t_env *env, int u)
{
	char	*name;
	
	if (str[parser->i] == '"' || str[parser->i] == '\'')
	{
		parser->is_quote = parser->is_quote |= (str[parser->i] == '"');
		parser->var = make_token(str + parser->i, &parser->i, str[parser->i], env);
		if (parser->var == NULL)
			return (3);
		parser->read = ft_strdupcat(parser->read, parser->var, (int)ft_strlen(parser->var));
		free(parser->var);
		return (1);
	}
	else if (str[parser->i] == '$' && parser->type != R_REDIR_IN)
	{
		name = pull_varname(str + parser->i, &u);
		if (ft_strlen(name) > 0)
		{
			parser->i += u;
			var_lector(parser->cursor, name, &parser->read, env);
			free(name);
			return (1);
		}
		free(name);
	}
	return (0);
}

int	fill_token_list(t_parsing *parser, t_main *m)
{
	int res;
	
	res = 0;
	while (m->line[parser->i] == ' ')
	{
		fill_args(&parser->read, &parser->type, parser->cursor, &parser->is_quote);
		parser->i++;
	}
	if (m->line[parser->i] == ';' || m->line[parser->i] == '\\')
		return (5);
	if (m->line[parser->i] == '|')
	{
		fill_args(&parser->read, &parser->type, parser->cursor, &parser->is_quote);
		if (parser->cursor->cmds_av == NULL && parser->cursor->file == NULL)
			return (4);
		next_token(&parser->cursor, m->line[parser->i++] == '|');
		return (1);
	}
	res = redir_manager(parser, m->line);
	if (res != 0)
		return (res);
	res = quote_manager(parser, m->line, m->env, 0);
	if (res != 0)
		return (res);
	return (0);
}

t_token	*ft_parsing(t_main *m)
{
	t_parsing	parser;
	int			res;

	if (!m->line)
		return (NULL);
	parser.i = 0;
	parser.read = NULL;
	parser.cursor = init_token();
	parser.list = parser.cursor;
	parser.is_quote = 0; 
	parser.type = DEFAULT;
	while(m->line[parser.i])
	{
		res = fill_token_list(&parser, m);
		if (res == 1)
			continue;
		if (res > 1 )
			return (NULL);
		if (m->line[parser.i])
			parser.read = ft_strdupcat(parser.read, m->line + parser.i++, 1);
	}
	fill_args(&parser.read, &parser.type, parser.cursor, &parser.is_quote);
	if (parser.cursor->cmds_av == NULL && parser.cursor->file == NULL)
		return (NULL);
	return (parser.list);
}