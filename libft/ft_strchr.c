/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:05:23 by abonard           #+#    #+#             */
/*   Updated: 2021/12/09 12:19:26 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	i = 0;
	cc = (char)c;
	while ((s[i]) && (s[i]) != cc)
		i++;
	if ((cc == 0) && (s[i]) == '\0')
		return ((char *)s + ft_strlen(s));
	if (s[i] == cc)
		return ((char *)s + i);
	return (NULL);
}
