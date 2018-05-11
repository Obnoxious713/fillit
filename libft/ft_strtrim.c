/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:11:56 by jfleisch          #+#    #+#             */
/*   Updated: 2018/03/08 17:54:24 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			index_ls(char const *str)
{
	int				i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
		i++;
	return (i);
}

static int			index_rs(char const *str)
{
	int				len;

	len = ft_strlen(str);
	if (len == 0)
		return (0);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n'
			|| str[len - 1] == '\t'))
		len--;
	return (len);
}

char				*ft_strtrim(char const *s)
{
	int				start;
	int				len;

	if (!s)
		return (NULL);
	start = index_ls(s);
	len = index_rs(s) - start;
	if (len <= 0)
		return (ft_strnew(0));
	return (ft_strsub(s, start, len));
}
