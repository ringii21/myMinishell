/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:38:36 by abonard           #+#    #+#             */
/*   Updated: 2022/08/22 18:54:29 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCT_H

# define FT_STRUCT_H

# include <unistd.h>
# include <stdarg.h>

typedef struct s_print
{
	long long int		nbr;
	unsigned long int	nb;
	va_list				args;
	int					pct;
	int					wdt;
	int					prc;
	int					zero;
	int					dash;
	int					total_value;
	int					sign;
	int					sp;
}	t_print;

#endif
