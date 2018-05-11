/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:59:30 by jfleisch          #+#    #+#             */
/*   Updated: 2018/03/08 18:03:44 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strnstr(const char *hay, const char *need, size_t len)
{
	size_t			i;
	size_t			j;

	i = 0;
	if (!*need)
		return ((char*)hay);
	while (hay[i] && i < len)
	{
		j = 0;
		while (hay[i + j] == need[j] && i + j < len)
		{
			j++;
			if (!need[j])
				return ((char*)hay + i);
		}
		i++;
	}
	return (NULL);
}
