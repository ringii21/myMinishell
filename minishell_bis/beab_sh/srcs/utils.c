/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:01:02 by seozcan           #+#    #+#             */
/*   Updated: 2022/09/29 18:10:26 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*void	ft_error(const char *str)*/
/*{  */
/* 	write(2, "ERR: ", 5); */
/* 	write(2, str, ft_strlen(str)); */
/* 	if (ft_strnstr(strerror(errno), "Success", 7) == 0) */
/* 		write(2, strerror(errno), ft_strlen(strerror(errno))); */
/* 	write(2, "\n", 1); */
/* 	exit(EXIT_FAILURE);
}*/

void	ft_error(void)
{
	perror(strerror(errno));
	exit(EXIT_FAILURE);
}

void	*xmalloc(size_t size)
{
	void	*tmp;

	tmp = malloc(size);
	if (!tmp)
		ft_error();
	return (tmp);
}
