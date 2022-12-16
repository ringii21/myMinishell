/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:41:11 by root              #+#    #+#             */
/*   Updated: 2022/12/17 00:19:53 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	quote_manager(t_main *m, t_parse *p, char *str, t_env *env)
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
		name = pull_varname(str + p->i, &m->u);
		if (ft_strlen(name) > 0)
		{
			p->i += m->u;
			var_lector(m->cursor, name, &p->read, env);
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
		fill_args(&p->read, &p->type, m->cursor, &p->is_quote);
		p->i++;
	}
	if (tmp[p->i] == '\\')
		return (5);
	if (tmp[p->i] == '|')
	{
		fill_args(&p->read, &p->type, m->cursor, &p->is_quote);
		if (m->cursor->cmds_av == NULL && m->cursor->file == NULL)
			return (4);
		next_token(&m->cursor, tmp[p->i++] == '|');
		return (1);
	}
	res = redir_manager(m, p, tmp);
	if (res != 0)
		return (res);
	res = quote_manager(m, p, tmp, m->env);
	if (res != 0)
		return (res);
	return (0);
}

int	parse_flush(t_main *m, char *tmp, int res)
{
	if (res == 1)
	{
		if (tmp[m->p->i] == '?' && tmp[m->p->i - 1] && tmp[m->p->i - 1] == '$')
			m->p->i++;
		return (2);
	}
	if (res > 1)
	{
		free(tmp);
		ft_flush(m->t);
		return (0);
	}
	return (3);
}

t_token	*parser(t_main *m)
{
	int		res;
	char	*tmp;

	tmp = lexer(m);
	if (!tmp)
		return (NULL);
	m->t = init_token();
	m->cursor = m->t;
	while (tmp[m->p->i])
	{	
		m->u = 0;
		res = fill_token_list(m->p, m, tmp);
		res = parse_flush(m, tmp, res);
		if (res == 0)
			return (NULL);
		else if (res != 2 && tmp[m->p->i])
			m->p->read = ft_strdupcat(m->p->read, tmp + m->p->i++, 1);
	}
	fill_args(&m->p->read, &m->p->type, m->cursor, &m->p->is_quote);
	if (m->cursor->cmds_av == NULL && m->cursor->file == NULL)
		return (NULL);
	free(tmp);
	count_ac(m->t);
	return (m->t);
}
