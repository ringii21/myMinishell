/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodeclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:28:08 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/20 18:34:10 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	free_nodes(t_node **nodes, void (*del)(void*))
{
	t_node	*next_elem;

	if (nodes)
	{
		while (*nodes)
		{
			next_elem = (*nodes)->next;
			delone_node(*nodes, del);
			(*nodes) = next_elem;
		}
	}
}
