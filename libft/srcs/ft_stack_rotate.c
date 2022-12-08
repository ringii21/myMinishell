/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:03:30 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/14 18:12:47 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	rotate(t_stack *s)
{
	void	*content;
	t_node	*tmp;

	if (stack_size(s) > 1)
	{
		tmp = s->head;
		if (!tmp)
			return ;
		content = tmp->data;
		s->head = tmp->next;
		s->head->prev = NULL;
		put_back(s, content);
		free(tmp);
	}
}
