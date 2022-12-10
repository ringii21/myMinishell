/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ringii <ringii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:25:46 by abonard           #+#    #+#             */
/*   Updated: 2022/12/10 16:01:21 by ringii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_cntlc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_cntl_slsh(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", 0);
}

void	ft_sig_ghost(int sig)
{
	(void)sig;
	if (sig == SIGINT)
		ft_putstr_fd("\n", 1);
}

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