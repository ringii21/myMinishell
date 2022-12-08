/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:42:51 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/08 15:31:41 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *pull_varvalue(char *varname, t_env *env)
 {
	char *path;

	if (varname[0] == '?' && !varname[1])
		return (NULL);
	path = get_cont(varname, env);
	if (path == NULL)
		return ("");
	return (path);
}

void	var_lector(t_token *cursor, char *var, char **reading, t_env *env)
{
	int	 i;
	char *str;
	char *r;

	str = pull_varvalue(var, env);
	i = 0;
	r = *reading;
	while (str[i])
	{
		while (str[i] == ' ')
		{
			fill_args(&r, NULL, cursor, NULL);
			i++;
		}
		if (str[i])
			r = ft_strdupcat(r, str + i++, 1);
	}
	*reading = r;
}

char	*pull_varname(char *str, int *cursor)
{
	int		i;
	char	*read;

	read = xmalloc(1);
	if (read == NULL)
		return (NULL);
	read[0] = 0;
	i = 1;
	if (str[i] == '?')
	{
		*cursor += i;
		return(ft_strdupcat(read, "?", 1));
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
		{
			*cursor += i;
			return (read);
		}
		read = ft_strdupcat(read, str + i++, 1);
	}
	*cursor += i;
	return (read);
}

int	expand_var(t_env *env, char **parser, int *i, char *str)
{
	char	*varname;
	char	*cont;
	int		j;
	if (str[*i] == '$')
	{
		j = 0;
		varname = pull_varname(str + (*i), &j);
		if (ft_strlen(varname) > 0)
		{
			*i += j;
			cont = pull_varvalue(varname, env);
			free(varname);
			*parser = ft_strdupcat(*parser, cont, (int)ft_strlen(cont));
			return (1);
		}
		free(varname);
	}
	return (0);
}

char *make_token(char *str, int *cursor, char c, t_env *env)
{
	int i;
	char *parser;

	i = 1;
	parser = xmalloc(1);
	if (parser == NULL)
		return (NULL);
	parser[0] = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			*cursor += i + 1;
			return (parser);
		}
		else if (c == '"' && expand_var(env, &parser, &i, str))
			continue;
		parser = ft_strdupcat(parser, str + i++, 1);
	}
	free(parser);
	parser = NULL;
	return (parser);
}
