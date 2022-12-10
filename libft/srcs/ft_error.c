/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:15:54 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/10 11:35:52 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_error(char *s)
{
	if (ft_strnstr(strerror(errno), "Success", 7) == 0)
	{
		perror(s);
		write(2, "\n", 1);
	}
	exit(EXIT_FAILURE);
}
