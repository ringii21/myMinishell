/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:05:48 by abonard           #+#    #+#             */
/*   Updated: 2021/12/07 19:08:37 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*csrc;
	char		*cdest;

	i = 0;
	csrc = (char *)src;
	cdest = (char *)dest;
	if (dest == src)
		return (dest);
	else if (cdest > csrc)
	{
		while (++i <= n)
			cdest[n - i] = csrc[n - i];
	}
	else
	{
		while (i < n)
		{
			cdest[i] = csrc[i];
			i++;
		}
	}
	return (dest);
}
