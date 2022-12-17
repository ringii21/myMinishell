/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 22:27:20 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/17 01:09:38 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_if_not_valid_pipes(char *line, int i, bool err, size_t len)
{
	if (line[0] == '|' || line[len - 1] == '|')
	{
		if (err == true)
			ft_putstr_fd(ERR_PIPE, STDERR_FILENO);
		g_status = 2;
		return (0);
	}
	while (line[++i])
	{
		if (line[i] == '|')
		{
			while (line[++i] && line[i] == ' ')
				;
			if (line[i] == '|')
			{
				if (err == true)
					ft_putstr_fd(ERR_PIPE, STDERR_FILENO);
				g_status = 2;
				return (0);
			}
		}
	}
	return (1);
}

int	ft_check_if_not_valid_redir(char *line, int i, bool err, size_t len)
{	
	if (line[len - 1] == '>' || line[len - 1] == '<')
	{
		if (err == true)
			ft_putstr_fd(ERR_NL, STDERR_FILENO);
		g_status = 2;
		return (0);
	}
	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (line[i + 1] == '>' || line[i + 1] == '<')
				i++;
			while (line[++i] == ' ')
				;
			if (line[i] == '|')
			{
				if (err == true)
					ft_putstr_fd(ERR_PIPE, STDERR_FILENO);
				g_status = 2;
				return (0);
			}
		}
	}
	return (1);
}

char	*lexer(t_main *m)
{
	char	*tmp;
	size_t	len;

	m->p = init_parser();
	m->quotes_empty = false;
	tmp = NULL;
	tmp = ft_strtrim(m->line, " \f\t\n\r\v");
	if (!tmp)
		return (NULL);
	len = ft_strlen(tmp);
	if (!len)
	{
		free(tmp);
		return (NULL);
	}
	if (!ft_check_if_not_valid_pipes(tmp, -1, true, len)
		|| !ft_check_if_not_valid_redir(tmp, -1, true, len)
		|| !check_quotes_is_valid(m, tmp) || !check_empty_quotes(m, tmp))
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
