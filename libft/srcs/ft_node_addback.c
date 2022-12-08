/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_addback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:31:52 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/14 18:55:27 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	putback_node(t_node **anode, t_node *new)
{
	t_node	*last_elem;

	if (anode)
	{
		if (*anode == NULL)
			*anode = new;
		else
		{
			last_elem = last_node(*anode);
			new->prev = last_elem;
			last_elem->next = new;
		}
	}
}
