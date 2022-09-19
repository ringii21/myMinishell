/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:12:07 by abonard           #+#    #+#             */
/*   Updated: 2021/12/09 13:01:29 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checking(char c, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*buff;
	int		i;
	int		z;

	if (!s1)
		return (NULL);
	i = 0;
	z = ft_strlen(s1) - 1;
	while ((s1[i]) && ft_checking(s1[i], set) == 1)
		i++;
	while ((s1[z]) && ((i < z) && ft_checking(s1[z], set) == 1))
		z--;
	buff = ft_substr(s1, i, (z - i) + 1);
	if (buff == NULL)
		return (NULL);
	return (buff);
}
