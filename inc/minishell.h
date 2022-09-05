#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


typedef struct s_env
{
    char    *var;
    char    *cont;
    char    *total;
    int     stat_code;
    struct s_env   *next;
}t_env;

int     ft_get_len_env(t_env *env);
int     ft_buildin_env(t_env *env);
int     ft_pwd(t_env *env);
int     ft_exit(t_env *env, char **cmds);
int     ft_shutup_signals(int fork);
int     ft_set_signals(void);
char    *get_cont(char *name_var, t_env *env);
char    **ft_list_to_tab(t_env *env);
t_env   *ft_put_env(char **envp);
t_env   *fill_env(char *is_env);


#endif