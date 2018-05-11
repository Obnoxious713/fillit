/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:10:21 by jfleisch          #+#    #+#             */
/*   Updated: 2018/02/21 15:11:09 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	slen;
	char			*dst;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen < start + len)
		return (NULL);
	dst = (char*)malloc(len + 1);
	if (!dst)
		return (NULL);
	ft_strncpy(dst, s + start, len);
	dst[len] = '\0';
	return (dst);
}
