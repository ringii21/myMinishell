/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 00:42:15 by abonard           #+#    #+#             */
/*   Updated: 2022/12/14 16:35:33 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_if_not_valid_pipes(char *line, int i)
{
	if (line[0] == '|' || line[ft_strlen(line) - 1] == '|')
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `|`\n", 2);
		g_status = 1;
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
				ft_putstr_fd("Minishell: syntax error near unexpected token `|`\n", 2);
				g_status = 127;
				return (0);
			}
		}
	}
	return (1);
}

int	ft_check_if_not_valid_redir(char *line, int i)
{
	if (line[ft_strlen(line) - 1] == '>' || line[ft_strlen(line) - 1] == '<')
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `newline'\n", 2);
		g_status = 2;
		return (0);
	}
	while (line[++i])
	{
		/*if (line[ft_strlen(line) - 1] == '>' || line[ft_strlen(line) - 1] == '<')
		{
			ft_putstr_fd("Minishell: syntax error near unexpected token `newline'\n", 2);
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
					ft_putstr_fd("Minishell: syntax error near unexpected token `|'\n", 2);
					g_status = 2;
					return (0);
				}
			} 
		}*/
	}
	return (1);
} 