/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:38:15 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/13 14:52:37 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*init_token(void)
{
	t_token	*cmd;

	cmd = ft_calloc(1 ,sizeof(t_token));
	if (cmd == NULL)
		return (NULL);
	return (cmd);
}

t_parse	init_parser(void)
{
	t_parse	new;
	
	new = (t_parse){0};
	new.list = init_token();
	new.cursor = new.list;
	return (new);
}
