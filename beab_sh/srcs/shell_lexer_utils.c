/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lexer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 00:42:15 by abonard           #+#    #+#             */
/*   Updated: 2022/12/16 22:31:24 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	check_len_and_line(char *line)
{
	size_t	len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	if (!len)
		return (0);
	return (len);
}

int	ft_check_if_not_valid_pipes(char *line, int i, bool err)
{
	size_t	len;

	len = check_len_and_line(line);
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

int	ft_check_if_not_valid_redir(char *line, int i, bool err)
{	
	size_t	len;

	len = check_len_and_line(line);
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

void	check_quotes(char c, int *b_quote, int *quotes)
{
	if (c == '"' || c == '\'')
	{
		if (*b_quote == 0)
		{
			*quotes += 1;
			if (c == '"')
				*b_quote = 1;
			else
				*b_quote = 2;
		}
		else
		{
			if ((*b_quote == 1 && c == '"') || (*b_quote == 2 && c == '\''))
			{
				*quotes += 1;
				*b_quote = 0;
			}
		}
	}
}

//Checking quotes functions
int	check_quotes_is_valid(char *line)
{
	int		i;
	int		quotes;
	int		b_quote;

	if (!line)
		return (1);
	i = -1;
	quotes = 0;
	b_quote = 0;
	while (line[++i])
	{
		check_quotes(line[i], &b_quote, &quotes);
		if (line[i] == '\\' && b_quote == 0)
			return (0);
	}
	if (quotes % 2 != 0)
	{
		ft_putstr_fd(ERR_QUOTE, STDERR_FILENO);
		return (0);
	}
	return (1);
}