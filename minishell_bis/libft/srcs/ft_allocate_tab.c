/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocate_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:44:01 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/22 16:20:20 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	**allocate_tab(int **tab, int size)
{
	int	i;

	i = 0;
	tab = (int **)malloc(sizeof(int *) * size);
	if (!tab)
		return (NULL);
	while (i < size)
	{
		tab[i] = (int *)malloc(sizeof(int) * 2);
		if (!tab[i])
		{
			free(tab);
			return (NULL);
		}
		i++;
	}
	return (tab);
}
