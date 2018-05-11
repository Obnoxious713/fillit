/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:50:58 by jfleisch          #+#    #+#             */
/*   Updated: 2018/02/21 14:51:32 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*d;
	unsigned char		ch;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	ch = (unsigned char)c;
	i = -1;
	while (++i < n)
	{
		*d = s[i];
		d++;
		if (ch == s[i])
			return (d);
	}
	return (NULL);
}
