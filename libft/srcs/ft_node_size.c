/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:54:50 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/14 18:56:26 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	node_size(t_node *n)
{
	size_t	size;

	size = 0;
	if (n)
	{
		while (n)
		{
			n = n->next;
			size++;
		}
		return (size);
	}
	return (0);
}
