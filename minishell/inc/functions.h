/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:49:51 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/22 16:30:48 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H

# define FUNCTIONS_H

# include "minishell.h"

//              get_next_line.c
char	*get_next_line(int fd);
char	*set_head(char *head);
char	*get_line(char *ln, char *head);
char	*append_lines(int fd, char *buff, char *head);

//              get_next_line_utils.c
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
size_t	ft_strlen_gnl(const char *str);

//				ft_xmalloc.c
void	*xmalloc(size_t size);

//				PIPEX
int		pipex(int ac, char **av, char **envp);

// 				pipex_cmds.c
void	ft_process(t_obj o, char **envp);

// 				pipex_utils.c
void	ft_error(const char *str);
void	ft_free_child(t_obj *obj);
void	ft_free_parent(t_obj *obj);
void	ft_close_pipes(t_obj *obj);

#endif