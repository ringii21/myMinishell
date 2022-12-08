/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodemap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:02:10 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/14 19:35:49 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_node	*node_map(t_node *nodes, void *(*f)(void *), void (*del)(void *))
{
	t_node	*new_nodes;
	t_node	*new_elem;

	new_elem = 0;
	new_nodes = NULL;
	while (nodes)
	{
		new_elem = new_node(f(nodes->data));
		if (!new_elem)
		{
			free_nodes(&new_nodes, del);
			return (NULL);
		}
		putback_node(&new_nodes, new_elem);
		nodes = nodes->next;
	}
	return (new_nodes);
}
