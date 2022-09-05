/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:05:11 by abonard           #+#    #+#             */
/*   Updated: 2022/01/26 15:20:46 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_number(t_print *print)
{
	int	num;

	if (!print)
		return (0);
	num = va_arg(print->args, int);
	ft_putnbr_fd(num, 1);
	print->total_value += ft_len(num);
	return (1);
}
