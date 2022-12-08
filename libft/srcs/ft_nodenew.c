/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:36:33 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/14 18:44:33 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_node	*new_node(void *content)
{
	t_node	*new;

	new = xmalloc(sizeof(t_node));
	new->data = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
