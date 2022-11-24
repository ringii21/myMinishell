/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:09:55 by seozcan           #+#    #+#             */
/*   Updated: 2021/11/26 17:39:14 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_basechr(char *base, int c)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

unsigned int	ft_atoi_hexa(const char *str)
{
	int				i;
	unsigned int	r;
	char			*base_lc;
	char			*base_uc;

	i = 0;
	r = 0;
	base_lc = "0123456789abcdef";
	base_uc = "0123456789ABCDEF";
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	i = 0;
	while (ft_basechr(base_lc, str[i]) >= 0 || ft_basechr(base_uc, str[i]) >= 0)
	{
		if (ft_basechr(base_lc, str[i]) >= 0)
			r = r * 16 + ft_basechr(base_lc, str[i]);
		else if (ft_basechr(base_uc, str[i]) >= 0)
			r = r * 16 + ft_basechr(base_uc, str[i]);
		i++;
	}
	return (r);
}
