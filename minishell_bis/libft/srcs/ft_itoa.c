/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:02:30 by seozcan           #+#    #+#             */
/*   Updated: 2021/11/27 15:02:44 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	ft_nlen(long int nb)
{
	size_t	len;

	len = 0;
	if (nb <= 0)
		len = 1;
	while (nb)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

static char	*ft_itoa_convert(char *r, long int nb, size_t nlen)
{
	while (nb)
	{
		r[nlen--] = (char)((nb % 10) + 48);
		nb /= 10;
	}
	return (r);
}

char	*ft_itoa(int n)
{
	long int	nb;
	size_t		nlen;
	char		*r;

	nlen = ft_nlen(n);
	nb = n;
	r = (char *)malloc(sizeof(char) * nlen + 1);
	if (!r)
		return (NULL);
	r[nlen--] = '\0';
	if (nb == 0)
	{
		r[0] = '0';
		return (r);
	}
	else if (nb < 0)
	{
		nb *= -1;
		r[0] = '-';
	}
	r = ft_itoa_convert(r, nb, nlen);
	return (r);
}
