/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:11:44 by abonard           #+#    #+#             */
/*   Updated: 2022/02/07 15:15:05 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_cfmt(t_print *print)
{
	char	c;

	c = va_arg(print->args, int);
	write(1, &c, 1);
	print->total_value += 1;
}

void	ft_ufmt(t_print *print)
{
	print->nbr = va_arg(print->args, unsigned int);
	ft_putnbr_base(print->nbr, "0123456789");
	print->total_value += ft_len(print->nbr);
}

void	ft_percent(t_print *print)
{
	write(1, "%", 1);
	print->pct = 1;
	print->total_value++;
}

int	ft_parsing(t_print *print, const char fmt)
{
	if (fmt == 'i' || fmt == 'd')
		ft_number(print);
	else if (fmt == 'c')
		ft_cfmt(print);
	else if (fmt == 's')
		ft_string(print);
	else if (fmt == 'p')
		ft_pfmt(print);
	else if (fmt == 'u')
		ft_ufmt(print);
	else if (fmt == 'x' || fmt == 'X')
		ft_xfmt(print, fmt);
	else if (fmt == '%' && print->pct == 0)
		ft_percent(print);
	else
	{
		if (print->pct == 1 && fmt == '%')
			print->pct = 0;
		else
		{
			write(1, &fmt, 1);
			print->total_value++;
		}
	}
	return (0);
}
