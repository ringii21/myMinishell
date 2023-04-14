/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_sig_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:00:43 by ringii            #+#    #+#             */
/*   Updated: 2022/12/16 20:54:10 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	set_signals(void)
{
	if (!(signal(SIGINT, ft_cntlc)))
		return (0);
	return (1);
}

int	set_sig(void)
{
	if (!signal(SIGQUIT, ft_cntl_slsh))
		return (0);
	return (1);
}
