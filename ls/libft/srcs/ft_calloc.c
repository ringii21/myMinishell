/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 17:23:11 by seozcan           #+#    #+#             */
/*   Updated: 2021/11/26 17:38:28 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	ptr = malloc(size * count);
	if (ptr)
		ft_bzero(ptr, count * size);
	return (ptr);
}
