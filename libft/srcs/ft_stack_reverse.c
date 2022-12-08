/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_reverse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:56:10 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/14 18:12:41 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	reverse(t_stack *s)
{
	t_node	*tmp;
	void	*content;

	if (stack_size(s) > 1)
	{
		tmp = s->tail;
		if (!tmp)
			return ;
		content = tmp->data;
		s->tail = tmp->prev;
		s->tail->next = NULL;
		put_front(s, content);
		free(tmp);
	}
}
