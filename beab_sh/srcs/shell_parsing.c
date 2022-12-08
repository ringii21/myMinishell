/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:41:11 by root              #+#    #+#             */
/*   Updated: 2022/12/08 17:54:49 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	next_token(t_token **cursor, int is_pipe)
{
	t_token	*tmp;

	tmp = *cursor;
	if (is_pipe)
		(*cursor)->is_pipe = is_pipe;
	(*cursor)->next = init_token();
	*cursor = (*cursor)->next;
	(*cursor)->prev = tmp;
}

int	quote_manager(t_parsing *p, char *str, t_env *env, int u)
{
	char	*name;
	
	if (str[p->i] == '"' || str[p->i] == '\'')
	{
		p->is_quote = p->is_quote |= (str[p->i] == '"');
		p->var = make_token(str + p->i, &p->i, str[p->i], env);
		if (p->var == NULL)
			return (3);
		p->read = ft_strdupcat(p->read, p->var, (int)ft_strlen(p->var));
		free(p->var);
		return (1);
	}
	else if (str[p->i] == '$' && p->type != R_REDIR_IN)
	{
		name = pull_varname(str + p->i, &u);
		if (ft_strlen(name) > 0)
		{
			p->i += u;
			var_lector(p->cursor, name, &p->read, env);
			free(name);
			return (1);
		}
		free(name);
	}
	return (0);
}

int	fill_token_list(t_parsing *p, t_main *m)
{
	int	res;
	
	res = 0;
	while (m->line[p->i] == ' ')
	{
		fill_args(&p->read, &p->type, p->cursor, &p->is_quote);
		p->i++;
	}
	if (m->line[p->i] == ';' || m->line[p->i] == '\\')
		return (5);
	if (m->line[p->i] == '|')
	{
		fill_args(&p->read, &p->type, p->cursor, &p->is_quote);
		if (p->cursor->cmds_av == NULL && p->cursor->file == NULL)
			return (4);
		next_token(&p->cursor, m->line[p->i++] == '|');
		return (1);
	}
	res = redir_manager(p, m->line);
	if (res != 0)
		return (res);
	res = quote_manager(p, m->line, m->env, 0);
	if (res != 0)
		return (res);
	return (0);
}

t_token	*ft_parsing(t_main *m)
{
	t_parsing	p;
	int			res;

	if (!m->line)
		return (NULL);
	p.i = 0;
	p.read = NULL;
	p.cursor = init_token();
	p.list = p.cursor;
	p.is_quote = 0; 
	p.type = DEFAULT;
	while(m->line[p.i])
	{
		res = fill_token_list(&p, m);
		if (res == 1)
			continue;
		if (res > 1 )
			return (NULL);
		if (m->line[p.i])
			p.read = ft_strdupcat(p.read, m->line + p.i++, 1);
	}
	fill_args(&p.read, &p.type, p.cursor, &p.is_quote);
	if (p.cursor->cmds_av == NULL && p.cursor->file == NULL)
		return (NULL);
	return (p.list);
}
