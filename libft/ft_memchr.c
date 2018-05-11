/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:52:13 by jfleisch          #+#    #+#             */
/*   Updated: 2018/03/08 18:15:06 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*p;
	char		b;

	p = s;
	b = c;
	i = -1;
	while (++i < n)
	{
		if (*p == b)
			return ((void*)p);
		p++;
	}
	return (NULL);
}
