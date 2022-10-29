/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 22:23:04 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/29 23:11:16 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_lexer(t_node *l)
{
	t_node	*tmp;
	int		i;

	tmp = l;
	i = 0;
	printf("::::::::::::::::::::::::::\n");
	printf("::\033[0;32m\tLEXICON\t\t\033[m::\n");
	printf("::::::::::::::::::::::::::\n");
	while (tmp)
	{
		printf("node #%d type = %d arg = %c\n", i,
			((t_lexer *)tmp->data)->type, ((t_lexer *)tmp->data)->arg);
		printf(".....................\n");
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
	printf("::::::::::::::::::::::::::\n");
	printf("::\033[0;35m\tTOKENS\t\t\033[m::\n");
	printf("::::::::::::::::::::::::::\n");
	while (tmp)
	{
		printf("node #%02d type = %02d av[%02i] = [%s]\n", i,
			((t_token *)tmp->data)->id, 0, ((t_token *)tmp->data)->av[0]);
		j = 1;
		while (((t_token *)tmp->data)->av[j])
		{
			printf("\t\t   av[%02i] = [%s]\n", j,
				((t_token *)tmp->data)->av[j]);
			j++;
		}
		printf(".....................\n");
		i++;
		tmp = tmp->next;
	}
}