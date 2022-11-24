/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 22:05:07 by seozcan           #+#    #+#             */
/*   Updated: 2021/11/29 20:30:52 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*s2;
	unsigned int	front;
	unsigned int	back;

	if (!s1)
		return (NULL);
	front = 0;
	back = (unsigned int)ft_strlen(s1) - 1;
	s2 = 0;
	while (s1[front] && ft_strchr(set, s1[front]))
		front++;
	while (s1[back] && ft_strchr(set, s1[back]) && back >= front)
		back--;
	s2 = ft_substr(s1, front, ((back - front) + 1));
	if (!s2)
		return (NULL);
	return (s2);
}
