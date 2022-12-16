/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:41:11 by root              #+#    #+#             */
/*   Updated: 2022/12/16 22:45:20 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	count_ac(t_token *t)
{
	while (t != NULL)
	{
		if (t->cmds_av)
			t->cmd_ac = ft_tablen(t->cmds_av);
		t = t->next;
	}
}

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

int	quote_manager(t_parse *p, char *str, t_env *env, int u)
{
	char	*name;

	if (str[p->i] == '"' || str[p->i] == '\'')
	{
		p->is_quote |= (str[p->i] == '"');
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

int	fill_token_list(t_parse *p, t_main *m, char *tmp)
{
	int	res;

	while (tmp[p->i] == ' ')
	{
		fill_args(&p->read, &p->type, p->cursor, &p->is_quote);
		p->i++;
	}
	if (tmp[p->i] == '\\')
		return (5);
	if (tmp[p->i] == '|')
	{
		fill_args(&p->read, &p->type, p->cursor, &p->is_quote);
		if (p->cursor->cmds_av == NULL && p->cursor->file == NULL)
			return (4);
		next_token(&p->cursor, tmp[p->i++] == '|');
		return (1);
	}
	res = redir_manager(p, tmp);
	if (res != 0)
		return (res);
	res = quote_manager(p, tmp, m->env, 0);
	if (res != 0)
		return (res);
	return (0);
}

void	parser(t_main *m)
{
	int		res;
	char	*tmp;

	tmp = lexer(m);
	while (tmp[m->p.i])
	{
		res = fill_token_list(&m->p, m, tmp);
		if (res == 1)
		{
			if (tmp[m->p.i] == '?' && tmp[m->p.i - 1] && tmp[m->p.i - 1] == '$')
				m->p.i++;
			continue ;
		}
		if (res > 1)
		{
			free(tmp);
			ft_flush(m->p.list);
			return ;
		}
		if (tmp[m->p.i])
			m->p.read = ft_strdupcat(m->p.read, tmp + m->p.i++, 1);
	}
	fill_args(&m->p.read, &m->p.type, m->p.cursor, &m->p.is_quote);
	if (m->p.cursor->cmds_av == NULL && m->p.cursor->file == NULL)
		return ;
	free(tmp);
	count_ac(m->p.list);
}
