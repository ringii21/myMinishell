/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:09:50 by abonard           #+#    #+#             */
/*   Updated: 2021/12/07 19:05:49 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(int nb)
{
	size_t	len;

	len = 0;
	if (nb == 0)
		return (1);
	else if (nb == -2147483648)
		return (11);
	else if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

void	ft_kourkipoutchek(long long *i, int *guy, char *tab)
{
	if (*i == 0)
		tab[0] = '0';
	else if (*i < 0)
	{
		tab[0] = '-';
		*i = *i * -1;
		*guy += 1;
	}
}

char	*ft_itoa(int n)
{
	char		*tab;
	int			len;
	int			guy;
	long long	i;

	guy = 0;
	len = ft_len(n);
	i = n;
	tab = malloc(sizeof(char) * (len + 1));
	if (tab == NULL)
		return (NULL);
	tab[len] = '\0';
	len--;
	ft_kourkipoutchek(&i, &guy, tab);
	while (len >= guy)
	{
		tab[len] = (i % 10) + '0';
		i /= 10;
		len--;
	}
	return (tab);
}
