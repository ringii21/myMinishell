/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:39:21 by abonard           #+#    #+#             */
/*   Updated: 2021/12/07 19:08:12 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			pos;
	unsigned char	*cs1;
	unsigned char	*cs2;

	pos = 0;
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	while (pos < n)
	{
		if (cs1[pos] != cs2[pos])
			return (cs1[pos] - cs2[pos]);
		pos++;
	}
	return (0);
}
