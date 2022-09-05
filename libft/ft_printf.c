/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:32:53 by abonard           #+#    #+#             */
/*   Updated: 2022/02/07 15:07:07 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *fmt, ...)
{
	int		i;
	t_print	print;

	i = 0;
	va_start(print.args, fmt);
	ft_initialise_tab(&print);
	while (fmt && fmt[i])
	{
		if ((fmt[i - 1] == '%') && (i > 0) && (print.pct == 0))
			ft_parsing(&print, fmt[i]);
		else if (fmt[i] != '%')
		{
			write(1, &fmt[i], 1);
			print.total_value++;
		}
		else
			print.pct = 0;
		i++;
	}
	return (print.total_value);
}
