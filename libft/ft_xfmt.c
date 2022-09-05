/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xfmt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:10:39 by abonard           #+#    #+#             */
/*   Updated: 2022/01/26 20:38:25 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_xfmt(t_print *print, const char fmt)
{
	print->nb = va_arg(print->args, unsigned int);
	if (fmt == 'x')
		ft_putnbr_base(print->nb, "0123456789abcdef");
	else
		ft_putnbr_base(print->nb, "0123456789ABCDEF");
	print->total_value += ft_len_hexa(print->nb);
}
