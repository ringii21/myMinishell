/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:51:29 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/14 18:12:29 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	push(t_stack *a, t_stack *b)
{	
	t_node	*tmp;
	void	*content;

	if (stack_size(b) != 0)
	{
		tmp = b->head;
		if (!tmp)
			return ;
		content = tmp->data;
		put_front(a, content);
		b->head = b->head->next;
		if (b->head)
			b->head->prev = NULL;
		free(tmp);
	}
}
