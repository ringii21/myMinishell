/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:30:21 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/29 23:12:15 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	token_len(t_main *m, t_node *l)
{	
	size_t	len;

	len = 0;
	m->type = ((t_lexer *)l->data)->type;
	while (l && (((t_lexer *)l->data)->type == m->type
			|| ((t_lexer *)l->data)->type == T_SPACE))
	{
		l = l->next;
		len++;
	}
	printf("tokenlen == %lu\n", len);
	return (len);
}

void	build_token(t_main *m)
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
//	m->buf = ft_strtrim(m->buf, " ");
	printf("m->buf = [%s]\n", m->buf);
}

t_token	*fill_token(t_main *m)
{
	t_token		*content;

	content = (t_token *)ft_calloc(1, (sizeof(t_token)));
	build_token(m);
	control_operator(content, m);
//	if (content->id != O_CMD)
//	{
//		free(m->buf);
//		build_token(m);
//	}
	content->av = shell_splitter(m->buf, m);
	free(m->buf);
	return (content);
}

t_token	*expand_tokens(t_main *m, t_node *tmp)
{
	t_token		*content;

	content = (t_token *)ft_calloc(1, (sizeof(t_token)));
	control_operator(content, m);
	content->av = ((t_token *)tmp->data)->av;
//	if (content->is_redir)
//		expand_io(m, content);
	if (content->is_piped) 
		pipe(content->pipe);
	content->bin_path = NULL;
	free(m->buf);
	return (content);
}

int	create_tokens(t_main *m)
{
	t_node	*tokens_tmp;

	m->tmp = m->lexicon;
	if (!m->tmp)
		return (0);
	m->tokens = NULL;
	tokens_tmp = NULL;
	m->i = 0;
	m->state = S_DEFAULT;
	while (m->tmp)
	{
		while (m->tmp && ((((t_lexer *)m->tmp->data)->type == T_SPACE)
				|| ((t_lexer *)m->tmp->data)->type == T_QUOTE))
			m->tmp = m->tmp->next;
		putback_node(&tokens_tmp, new_node(fill_token(m)));
	}
	while (tokens_tmp)
	{
		putback_node(&m->tokens, new_node(expand_tokens(m, tokens_tmp)));
		tokens_tmp = tokens_tmp->next;
	}
	free_parser(tokens_tmp);
	return (1);
}