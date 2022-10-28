/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:25:46 by abonard           #+#    #+#             */
/*   Updated: 2022/10/28 17:35:13 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	shut_signals(int fork)
{
	if (fork == 0)
	{
		if (!(signal(SIGINT, SIG_DFL)))
			return (0);
		if (!(signal(SIGQUIT, SIG_DFL)))
			return (0);
	}
	else
	{
		if (!(signal(SIGINT, ft_sig_ghost)))
			return (0);
		if (!(signal(SIGQUIT, ft_sig_ghost)))
			return (0);
	}
	return (1);
}

int	set_sig(void)
{
	if (!signal(SIGINT, ft_cntlc))
		return (0);
	return (1);
}

int	set_signals(void)
{
	if (!signal(SIGQUIT, ft_cntl_slsh))
		return (0);
	return (1);
}
