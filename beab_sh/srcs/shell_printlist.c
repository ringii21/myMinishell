/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_printlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:26:05 by seozcan           #+#    #+#             */
/*   Updated: 2022/12/11 13:31:36 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_redir(t_redir *r)
{
	t_redir	*tmp;
	int		i;

	tmp = r;
	i = 0;
	printf("::::::::::::::::::::::::::\n");
	printf("::\033[0;32m\tFILE\t\t\033[m::\n");
	printf("::::::::::::::::::::::::::\n");
	while (tmp)
	{
		printf("node #%02d type = %d\targ = [%s]\n", i,
			tmp->type, tmp->file_path);
		printf(".....................\n");
		i++;
		tmp = tmp->next;
	}
}

void	print_tokens(t_token *t)
{
	t_token	*tmp;
	int		i;
	int		j;

	tmp = t;
	i = 0;
	printf("::::::::::::::::::::::::::\n");
	printf("::\033[0;35m\tTOKENS\t\t\033[m::\n");
	printf("::::::::::::::::::::::::::\n");
	while (tmp)
	{
		if (tmp->cmds_av)
		{
			printf("node #%02d cmd_ac = %02lu\tav[%02i] = [%s]\n", i,
				tmp->cmd_ac, 0, tmp->cmds_av[0]);
			j = 1;
			while (tmp->cmds_av[j])
			{
				printf("\t\t\tav[%02i] = [%s]\n", j,
					tmp->cmds_av[j]);
				j++;
			}
		}
		if (tmp->file)
			print_redir(tmp->file);
		printf(".....................\n");
		i++;
		tmp = tmp->next;
	}
}