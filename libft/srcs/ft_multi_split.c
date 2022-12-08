/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:19:54 by seozcan           #+#    #+#             */
/*   Updated: 2022/10/15 17:36:44 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_scan(char c, char *charset)
{
	size_t	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (charset[i]);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

static size_t	ft_word_count(char const *str, char *charset)
{
	size_t	wcount;
	size_t	i;

	wcount = 0;
	i = 0;
	while (str[i])
	{
		if (ft_scan(str[i + 1], charset) && (!ft_scan(str[i], charset)))
			wcount++;
		i++;
	}
	return (wcount);
}

static void	ft_splitcat(char **dest, char const *str, char *charset)
{
	int	i;
	int	j;
	int	tabs;

	i = 0;
	tabs = 0;
	while (str[i])
	{
		if (ft_scan(str[i], charset))
			i++;
		else
		{
			j = 0;
			while (!ft_scan(str[i + j], charset))
				j++;
			dest[tabs] = malloc(sizeof(char) * (j + 1));
			dest[tabs] = ft_substr(str, i, j);
			i = i + j;
			tabs++;
		}
	}

}

char	**multi_split(char const *s, char *charset)
{
	size_t		wcount;
	char		**dest;

	wcount = ft_word_count(s, charset);
	dest = (char **)xmalloc(sizeof(char *) * (wcount + 1));
	if (dest == NULL)
		return (NULL);
	dest[wcount] = 0;
	ft_splitcat(dest, s, charset);
	return (dest);
}
