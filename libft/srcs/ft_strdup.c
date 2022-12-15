/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:22:30 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/15 15:05:02 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	void	*dest;

	len = ft_strlen(s1) + 1;
	dest = malloc(len);
	if (!len)
		return (NULL);
	return ((char *)ft_memcpy(dest, s1, len));
}
