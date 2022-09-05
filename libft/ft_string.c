/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:07:58 by abonard           #+#    #+#             */
/*   Updated: 2022/01/26 20:35:49 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_string(t_print *print)
{
	char	*str;

	str = va_arg(print->args, char *);
	ft_putstr_fd(str, 1);
	if (!str)
		print->total_value += ft_strlen_custom("(null)");
	else
		print->total_value += ft_strlen_custom(str);
	return (1);
}
