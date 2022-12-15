/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_signals_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:26:16 by abonard           #+#    #+#             */
/*   Updated: 2022/12/15 21:12:55 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ignore_sig(int sig)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigaction(sig, &sa, NULL);
}

void	set_signal_heredoc(void (*sig_handler)(int), int sig)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sig_handler;
	sigaction(sig, &sa, NULL);
}

void	interrupt_heredoc(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		ft_putstr_fd("\n", 1);
		exit(130);
	}
}
