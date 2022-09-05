/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:17:15 by abonard           #+#    #+#             */
/*   Updated: 2021/12/09 12:41:00 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	if (s2[i] == '\0')
		return ((char *)s1);
	else
	{
		while (s1[i])
		{
			x = 0;
			while ((s2[x] == s1[i + x]) && i + x < len)
			{
				if (s2[x + 1] == '\0')
					return ((char *)s1 + i);
				x++;
			}
			i++;
		}
	}
	return (NULL);
}
