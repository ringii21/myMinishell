/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:41:11 by root              #+#    #+#             */
/*   Updated: 2022/12/16 19:30:52 by seozcan          ###   ########.fr       */
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

t_token	*parser(t_main *m)
{
	t_parse	p;
	int		res;
	char	*tmp;

	if (!m->line)
		return (NULL);
	p = init_parser();
	tmp = NULL;
	tmp = ft_strtrim(m->line, " \f\t\n\r\v");
	if (!tmp)
		return (NULL);
	if (!ft_check_if_not_valid_pipes(tmp, -1, true)
		|| !ft_check_if_not_valid_redir(tmp, -1, true)
		|| !check_quotes_is_valid(tmp))
	{
		free(tmp);
		return (p.list);
	}
	while (tmp[p.i])
	{
		res = fill_token_list(&p, m, tmp);
		if (res == 1)
		{
			if (tmp[p.i] == '?' && tmp[p.i - 1]
				&& tmp[p.i - 1] == '$')
				p.i++;
			continue ;
		}
		if (res > 1)
			return (NULL);
		if (tmp[p.i])
			p.read = ft_strdupcat(p.read, tmp + p.i++, 1);
	}
	fill_args(&p.read, &p.type, p.cursor, &p.is_quote);
	if (p.cursor->cmds_av == NULL && p.cursor->file == NULL)
		return (NULL);
	free(tmp);
	count_ac(p.list);
	return (p.list);
}
