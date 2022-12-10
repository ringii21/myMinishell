/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:38:15 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/10 09:49:13 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*init_token(void)
{
	t_token	*cmd;

	cmd = xmalloc(sizeof(t_token));
	if (cmd == NULL)
		return (NULL);
	cmd->cmds_av = NULL;
	cmd->cmd_ac = 0;
	cmd->is_pipe = false;
	cmd->is_pipe_open = 0;
	cmd->av_copy = NULL;
	cmd->path = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	cmd->file = NULL;
	return (cmd);
}

t_parse	init_parser(void)
{
	t_parse	new;
	
	new.i = 0;
	new.read = NULL;
	new.cursor = init_token();
	new.list = new.cursor;
	new.is_quote = 0;
	new.type = DEFAULT;
	return (new);
}
