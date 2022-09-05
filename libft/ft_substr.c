/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:15:28 by abonard           #+#    #+#             */
/*   Updated: 2021/12/09 13:39:06 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	i;
	unsigned int	length;

	if (!s)
		return (NULL);
	i = 0;
	length = ft_strlen(s);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	else if (len > length)
		dest = malloc(sizeof(char) * (length - start + 1));
	else
		dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (len-- && (length >= start))
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}
