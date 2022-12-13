/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:38:15 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/13 16:03:13 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*init_token(void)
{
	t_token	*new_token;

	new_token = ft_calloc(1 ,sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	return (new_token);
}

t_parse	init_parser(void)
{
	t_parse	new;
	
	new = (t_parse){0};
	new.list = init_token();
	new.cursor = new.list;
	return (new);
}
