/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:24:30 by seozcan           #+#    #+#             */
/*   Updated: 2021/11/26 18:38:24 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*d;
	unsigned int	i;
	unsigned int	slen;

	if (!s)
		return (NULL);
	i = 0;
	slen = (unsigned int)ft_strlen(s);
	if (start >= slen)
	{
		d = (char *)malloc(sizeof(char) * 1);
		d[i] = '\0';
		return (d);
	}
	else if (len >= slen)
		d = (char *)malloc(sizeof(char) * ((slen - start) + 1));
	else
		d = (char *)malloc(sizeof(char) * (len + 1));
	if (!d)
		return (NULL);
	while (len-- && s[start])
		d[i++] = s[start++];
	d[i] = '\0';
	return (d);
}
