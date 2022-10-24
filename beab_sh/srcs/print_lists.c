/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 22:23:04 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/24 23:12:59 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_lexer(t_node *l)
{
	t_node	*tmp;
	int		i;

	tmp = l;
	i = 0;
	while (tmp)
	{
		printf(" Lexer node #%d type = %d arg = %c\n", i,
			((t_lexer *)tmp->data)->type, ((t_lexer *)tmp->data)->arg);
		printf(" ------------------ \n");
		i++;
		tmp = tmp->next;
	}
}

void	print_parser(t_node *p)
{
	t_node	*tmp;
	int		i;
	int		j;

	tmp = p;
	i = 0;
	while (tmp)
	{
		printf(" Token node #%d type = %d av[%i] = %s\n", i,
			((t_token *)tmp->data)->id, 0, ((t_token *)tmp->data)->av[0]);
		j = 1;
		while (((t_token *)tmp->data)->av[j])
		{
			printf("                  av[%i] = %s\n", j,
				((t_token *)tmp->data)->av[j]);
			j++;
		}
		printf(" ------------------ \n");
		i++;
		tmp = tmp->next;
	}
}
