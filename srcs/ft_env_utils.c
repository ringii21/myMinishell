#include "../inc/minishell.h"

t_env   *fill_env(char *is_env)
{
    t_env   *new;
    char    **tab;

     new = malloc(sizeof(t_env) * 1);
     if (new == NULL)
        return (NULL);
    new->next = NULL;
    new->total = is_env;
    tab = ft_split(new->total, '=');
    new->var = ft_strdup(tab[0]);
    new->cont = ft_strdup(tab[1]);
    if (tab == NULL || new->var == NULL|| new->cont == NULL)
        return (NULL); 
    ft_free_stab(tab);
    return (new);
}

int ft_get_len_env(t_env *env)
{
    t_env *tmp;
    int i;
    
    i = 0;
    tmp = env;
    while (tmp)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}

char *get_cont(char *name_var, t_env *env)
{
    t_env   *tmp;

    tmp = env;
    while (tmp)
    {
        if (ft_strcmp(name_var, tmp->var) == 0)
            return (tmp->cont);
        tmp = tmp->next;
    }
    return (NULL);
}

char **ft_list_to_tab(t_env *env)
{
    char **tab;
    t_env *tmp;
    int i;
    int len;

    i = 0;
    tmp = env;
    len = ft_get_len_env(tmp);
    tab = malloc(sizeof (char*) * len);
    if (tab == NULL)
        return (NULL);
    while (tmp)
    {
        tab[i] =  ft_strdup(tmp->total);
        if (tab[i] == NULL)
            return (NULL);
        tmp = tmp->next;
        i++;
    }
    return (tab);
}

t_env    *ft_put_env(char **envp)
{
    int i;
    t_env   *tmp;
    t_env   *res;

    i = 1;
    res = fill_env(envp[0]);
    tmp = res;
    while (envp[i])
    {
        tmp->next = fill_env(envp[i]);
        tmp = tmp->next;
        i++;
    }
    return (res);
}