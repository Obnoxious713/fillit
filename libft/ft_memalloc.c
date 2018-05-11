/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:04:43 by jfleisch          #+#    #+#             */
/*   Updated: 2018/02/21 15:05:02 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void		*ptr;

	if (size)
	{
		ptr = (void *)malloc(sizeof(*ptr) * (size));
		if (ptr)
		{
			ft_memset(ptr, 0, size);
			return (ptr);
		}
	}
	return (NULL);
}
