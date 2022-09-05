/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:36:24 by abonard           #+#    #+#             */
/*   Updated: 2022/01/27 12:27:28 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "ft_struct.h"

void	ft_bzero(void *s, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_strcpy(char *dest, char *src);
void	ft_initialise_tab(t_print *tab);
void	ft_xfmt(t_print *print, const char fmt);
void	ft_pfmt(t_print *print);
void	ft_putnbr_base(unsigned long long int nbr, char *base);
int		ft_strlen_custom(char *str);
int		ft_number(t_print *t_print);
int		ft_string(t_print *print);
int		ft_len(unsigned long long int nbr);
int		ft_len_hexa(unsigned long long int nbr);
int		ft_parsing(t_print *print, const char fmt);
int		ft_printf(const char *fmt, ...);

#endif
