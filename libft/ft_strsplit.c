/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:12:28 by jfleisch          #+#    #+#             */
/*   Updated: 2018/03/08 17:01:48 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			get_nbr_words(char const *s, char c)
{
	int				nbr_words;
	int				last_space;

	nbr_words = 0;
	last_space = 1;
	while (*s)
	{
		if (last_space && *s != c)
		{
			nbr_words++;
			last_space = 0;
		}
		else if (*s == c)
			last_space = 1;
		s++;
	}
	return (nbr_words);
}

static int			get_next_word(char const *s, int pos, char c)
{
	while (s[pos] == c)
		pos++;
	return (pos);
}

static int			get_word_len(char const *s, int pos, char c)
{
	int				len;

	len = 0;
	while (!(s[pos + len] == c || s[pos + len] == '\0'))
		len++;
	return (len);
}

static int			set_word(char **dst, char const *str, char c, int pos)
{
	int				i;

	i = get_word_len(str, pos, c);
	*dst = ft_strsub(str, pos, i);
	return (pos + i);
}

char				**ft_strsplit(const char *s, char c)
{
	int				i;
	int				pos;
	int				words;
	char			**res;

	i = 0;
	pos = 0;
	if (!s)
		return (NULL);
	words = get_nbr_words(s, c);
	res = (char**)malloc(sizeof(char*) * (words + 1));
	if (!res)
		return (NULL);
	while (i < words)
	{
		pos = get_next_word(s, pos, c);
		pos = set_word(&res[i], s, c, pos);
		i++;
	}
	res[i] = 0;
	return (res);
}
