/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_swap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:06:21 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/14 18:19:50 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	swap(t_stack *s)
{
	void	*content1;
	void	*content2;

	if (stack_size(s) > 1)
	{
		content1 = s->head->data;
		content2 = s->head->next->data;
		s->head->data = content2;
		s->head->next->data = content1;
	}
}
