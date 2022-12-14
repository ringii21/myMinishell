/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:41:11 by root              #+#    #+#             */
/*   Updated: 2022/12/14 15:00:34 by abonard          ###   ########.fr       */
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

int	fill_token_list(t_parse *p, t_main *m)
{
	int res;

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

t_token	*parser(t_main *m)
{
	t_parse	p;
	int		res;

	if (!m->line)
		return (NULL);
	p = init_parser();
	if (!ft_check_if_not_valid_pipes(m->line, -1) || !ft_check_if_not_valid_redir(m->line, -1))
		return (p.list);
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
	count_ac(p.list);
	return (p.list);
}
