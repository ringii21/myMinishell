/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:13:54 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/10 11:36:25 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*xmalloc(size_t size)
{
	void	*tmp;

	tmp = malloc(size);
	if (!tmp)
		ft_error(NULL);
	return (tmp);
}
