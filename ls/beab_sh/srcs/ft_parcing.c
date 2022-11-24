#include "../inc/minishell.h"

t_obj	*init_cmd(void)
{
	t_obj *cmd;

	cmd = malloc(sizeof(t_obj));
	if (cmd == NULL)
		return (NULL);
	cmd->cmds_av = NULL;
	cmd->cmd_ac = 0;
	cmd->is_pipe = false;
	cmd->is_pipe_o = 0;
	cmd->av_copy = NULL;
	cmd->path = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	cmd->file = NULL;
	return (cmd);

}

void	split_args(t_obj *obj, char *str)
{
	int		i;
	int 	j;
	char 	**tab;

	i = 0;
	while (obj->cmds_av && obj->cmds_av[i])
		i++;
	j = 0;
	tab = malloc(sizeof(char *) * ((unsigned long)i + 2));
	if (tab == NULL)
		return ;
	while (j < i)
	{
		tab[j] = obj->cmds_av[j];
		j++;
	}
	tab[j++] = str;
	tab[j] = NULL;
	if (obj->cmds_av != NULL)
		free(obj->cmds_av);
	obj->cmds_av = tab;

}

void	fill_redir(t_obj *obj, char *str, enum redir_type type, bool *is_quote)
{
	t_list_f *new;
	t_list_f *tmp;

	new = malloc(sizeof(t_list_f));
	if (new == NULL)
		return ;
	new->path = str;
	new->type = type;
	new->next = NULL;
	if (is_quote)
		new->is_quote = *is_quote;
	else
		new->is_quote = false;
	if (!obj->file)
		obj->file = new;
	else
	{
		tmp = obj->file;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void  fill_args(char **str, enum redir_type *type, t_obj *obj, bool *is_quote)
{
	if (*str && **str)
	{
		if (!type || *type == NONE)
			split_args(obj, *str);
		else
			fill_redir(obj, *str, *type, is_quote);
		if (is_quote)
			*is_quote = false;
		*str = NULL;
		if (type)
			*type = NONE;
	}	
}

void go_to_next_obj(t_obj **ici, int is_pipe)
{
	t_obj *tmp;

	tmp = *ici;
	if (is_pipe)
		(*ici)->is_pipe = is_pipe;
	(*ici)->next = init_cmd();
	*ici = (*ici)->next;
	(*ici)->prev = tmp;
}

int	ft_begin_w(char *is_out, char *is_in)
{
	while(*is_in)
	{
		if(!*is_out)
			return(0);
		if (*is_out != *is_in)
			return (0);
		++is_out;
		++is_in;
	}
	return (1);
}

int	ft_redir_manager(t_parcing *var, char *str)
{
	if (str[var->i] == '<' || str[var->i] == '>')
	{
		fill_args(&var->read, &var->type, var->ici, &var->is_quote);
		if (var->type != NONE)
			return (3);
		if (ft_begin_w(str + var->i, "<<") && ++var->i)
			var->type = R_REDIR_IN;
		else if (ft_begin_w(str + var->i, ">>") && ++var->i)
			var->type = R_REDIR_OUT;
		else if (ft_begin_w(str + var->i, ">") && !ft_begin_w(str + var->i, "<"))
			var->type = REDIR_OUT;
		else if (ft_begin_w(str + var->i, "<") && !ft_begin_w(str + var->i, ">"))
			var->type = REDIR_IN;
		else
			return (3);
		var->i++;
		return (1);
	}
	return (0);
}

char *ft_strdupcat(char *s, char *o, int len)
{
	int		i;
	int		j;
	char	*n;

	n = malloc(ft_strlen(s) + (size_t)len + 2);
	if (n == NULL)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		n[i] = s[i];
		i++;
	}
	j = 0;
	while (j < len)
	{
		n[i + j] = o[j];
		j++;
	}
	n[i + j] = 0;
	if (s)
		free(s);
	return (n);
}

 char *pull_varvalue(char *varname, t_env *env)
 {
	char *path;

	if (varname[0] == '?' && !varname[1])
		return (NULL);
	path = get_cont(varname, env);
	if (path == NULL)
		return ("");
	return (path);
 }

char	*pull_varname(char *str, int *ici)
{
	int		i;
	char	*read;

	read = malloc(1);
	if (read == NULL)
		return (NULL);
	read[0] = 0;
	i = 1;
	if (str[i] == '?')
	{
		*ici += i;
		return(ft_strdupcat(read, "?", 1));
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
		{
			*ici += i;
			return (read);
		}
		read = ft_strdupcat(read, str + i++, 1);
	}
	*ici += i;
	return (read);

}

int	make_token_bis(t_env *env, char **token, int *i, char *str)
{
	char	*varname;
	char	*cont;
	int		j;
	if (str[*i] == '$')
	{
		j = 0;
		varname = pull_varname(str + (*i), &j);
		if (ft_strlen(varname) > 0)
		{
			*i += j;
			cont = pull_varvalue(varname, env);
			free(varname);
			*token = ft_strdupcat(*token, cont, (int)ft_strlen(cont));
			return (1);
		}
		free(varname);
	}
	return (0);
}

char *make_token(char *str, int *ici, char c, t_env *env)
{
	int i;
	char *token;

	i = 1;
	token = malloc(1);
	if (token == NULL)
		return (NULL);
	token[0] = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			*ici += i + 1;
			return (token);
		}
		else if (c == '"' && make_token_bis(env, &token, &i, str))
			continue;
		token = ft_strdupcat(token, str + i++, 1);
	}
	free(token);
	token = NULL;
	return (token);
}

void	var_lector(t_obj *ici, char *var, char **reading, t_env *env)
{
	int i;
	char *str;
	char *r;

	str = pull_varvalue(var, env);
	i = 0;
	r = *reading;
	while (str[i])
	{
		while (str[i] == ' ')
		{
			fill_args(&r, NULL, ici, NULL);
			i++;
		}
		if (str[i])
			r = ft_strdupcat(r, str + i++, 1);
	}
	*reading = r;
}

int	quote_manager(t_parcing *var, char *str, t_env *env, int u)
{
	char	*name;
	if (str[var->i] == '"' || str[var->i] == '\'')
	{
		var->is_quote = var->is_quote |= (str[var->i] == '"');
		var->var = make_token(str + var->i, &var->i, str[var->i], env);
		if (var->var == NULL)
			return (3);
		var->read = ft_strdupcat(var->read, var->var, (int)ft_strlen(var->var));
		free(var->var);
		return (1);
	}
	else if (str[var->i] == '$' && var->type != R_REDIR_IN)
	{
		name = pull_varname(str + var->i, &u);
		if (ft_strlen(name) > 0)
		{
			var->i += u;
			var_lector(var->ici, name, &var->read, env);
			free(name);
			return (1);
		}
		free(name);
	}
	return (0);
}

int	ft_allez_parce_1(t_parcing *var, t_main *m)
{
	int res;
	while (m->line[var->i] == ' ')
	{
		fill_args(&var->read, &var->type, var->ici, &var->is_quote);
		var->i++;
	}
	if (m->line[var->i] == ';' || m->line[var->i] == '\\')
		return (5);
	if (m->line[var->i] == '|')
	{
		fill_args(&var->read, &var->type, var->ici, &var->is_quote);
		if (var->ici->cmds_av == NULL && var->ici->file == NULL)
			return (4);
		go_to_next_obj(&var->ici, m->line[var->i++] == '|');
		return (1);
	}
	res = ft_redir_manager(var, m->line);
	if (res != 0)
		return (res);
	res = quote_manager(var, m->line, m->env, 0);
	if (res != 0)
		return (res);
	return (0);
}

t_obj	*ft_parcing(t_main *m)
{
	t_parcing	var;
	int		res;

	if (!m->line)
		return (NULL);
	var.i = 0;
	var.read = NULL;
	var.ici = init_cmd();
	var.list = var.ici;
	var.is_quote = 0; 
	var.type = NONE;
	while(m->line[var.i])
	{
		res = ft_allez_parce_1(&var, m);
		if (res == 1)
			continue;
		if (res > 1 )
			return (NULL);
		if (m->line[var.i])
			var.read = ft_strdupcat(var.read, m->line + var.i++, 1);
	}
	fill_args(&var.read, &var.type, var.ici, &var.is_quote);
	if (var.ici->cmds_av == NULL && var.ici->file == NULL)
		return (NULL);
	return (var.list);
}