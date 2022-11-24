/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:54:37 by seozcan           #+#    #+#             */
/*   Updated: 2021/11/18 00:55:53 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	a;

	i = 0;
	a = (char)c;
	while (s[i])
		i++;
	if (s[i] == '\0' && a == 0)
		return ((char *)s + ft_strlen(s));
	while (i--)
		if (s[i] == a)
			return ((char *)s + i);
	return (NULL);
}
