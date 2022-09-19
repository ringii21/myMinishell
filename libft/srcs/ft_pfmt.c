/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfmt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:19:10 by abonard           #+#    #+#             */
/*   Updated: 2022/01/26 20:21:22 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pfmt(t_print *print)
{
	print->nbr = va_arg(print->args, unsigned long long int);
	ft_putstr_fd("0x", 1);
	ft_putnbr_base(print->nbr, "0123456789abcdef");
	print->total_value += ft_len_hexa(print->nbr) + 2;
}
