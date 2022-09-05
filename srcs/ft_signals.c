#include "../inc/minishell.h"

void    ft_cntlc(int sig)
{
    (void)sig;
    ft_putstr_fd(" \b\b", 0);
    ft_putstr_fd("\n", 1);
}

void    ft_cntl_slsh(int sig)
{
    (void)sig;
    ft_putstr_fd(" \b\b", 0);
}

void    ft_sig_ghost(int sig)
{
    (void)sig;
    if (sig == SIGINT)
        ft_putstr_fd("\n", 1);
}

int ft_shutup_signals(int fork)
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

int ft_set_signals(void)
{
    if (!(signal(SIGINT, ft_cntlc)))
        return (0);
    if (!(signal(SIGQUIT, ft_cntl_slsh)))
        return (0);
    return (1);
}
