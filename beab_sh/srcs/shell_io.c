/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:02:08 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/22 18:58:08 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_open(t_redir *data, int flags, int mode)
{	
	data->fd = open(data->path, flags, mode);
	if (data->fd == -1)
		ft_error();
}

//void	heredoc(t_redir *data, t_main *m)
//{
//	char		*buf;
//
//	while (1)
//	{	
//		write(1, "\n", 1);
//		rl_replace_line("", 0);
//		rl_on_new_line();
//		buf = readline("");
//		if (ft_strcmp(buf, m->buf))
//			break ;
//		/*trouver un moyen de append le buf dans le fichier*/
//	}
//	pipes(m);
//	unlink(data->path);
//}

size_t	redir_len(t_main *m, t_node *l)
{	
	size_t	len;

	len = 0;
	m->type = ((t_lexer *)l->data)->type;
	while (l && (((t_lexer *)l->data)->type == m->type)
	{
		l = l->next;
		len++;
	}
	return (len);
}

char	*redir_splitter(t_main *m, t_redir *content)
{
	m->buf = NULL;
	m->i = 0;
	m->buf = xmalloc(sizeof(char) * (token_len(m, m->tmp) + 1));
	while (m->tmp && (((t_lexer *)m->tmp->data)->type == m->type
			|| ((t_lexer *)m->tmp->data)->type == T_SPACE))
	{
		m->buf[m->i] = ((t_lexer *)m->tmp->data)->arg;
		m->tmp = m->tmp->next;
		m->i++;
	}	
	m->buf[m->i] = '\0';
	m->buf = f_strtrim(m->buf, " ");
	content->data = ft_substr(m->buf, m->i, m->j);
	m->buf = ft_substr(m->buf, m->j, ft_strlen(m->buf) - m->j)
}

void	expand_io(t_redir *data)
{
	build_token(m);
	data->path = redir_splitter(m, data);
	if (data->id == O_STDIN_REDIR)
		ft_open(data, O_RDONLY, 0);
	else if (data->id == O_STDOUT_REDIR || data->id == O_DELEM)
		ft_open(data, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (data->id == O_APPEN)
		ft_open(data, O_APPEND | O_WRONLY, 0644);
}
