/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_addfront.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:52:42 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/14 19:21:18 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	putfront_node(t_node **anode, t_node *new)
{
	if (anode && new)
	{
		new->next = *anode;
		*anode = new;
	}
}
