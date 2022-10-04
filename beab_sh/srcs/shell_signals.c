/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:25:46 by abonard           #+#    #+#             */
/*   Updated: 2022/10/04 20:36:07 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_cntlc(int sig)
{
	(void)sig;
	ft_putstr_fd(" \b\n", 0);
	ft_putstr_fd(getenv("PWD"), 0);
	ft_putstr_fd("$", 1);
}

void	ft_cntl_slsh(int sig)
{
	(void)sig;
	ft_putstr_fd(" \b\b", 0);
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
		if (!(signal(SIGINT, ft_cntlc)))
			return (0);
		if (!(signal(SIGQUIT, ft_cntl_slsh)))
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

int	set_signals(void)
{
	if (!(signal(SIGINT, ft_cntlc)))
		return (0);
	if (!(signal(SIGQUIT, ft_cntl_slsh)))
		return (0);
	return (1);
}
