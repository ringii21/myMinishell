/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:10:29 by abonard           #+#    #+#             */
/*   Updated: 2022/01/26 20:34:34 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base(unsigned long long int nbr, char *base)
{
	unsigned long long int	size;
	unsigned long long int	guy;

	guy = nbr;
	size = ft_strlen_custom(base);
	if (guy >= size)
	{
		ft_putnbr_base(guy / size, base);
		ft_putchar_fd(base[guy % size], 1);
	}
	else
		ft_putchar_fd(base[guy % size], 1);
}
