/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:05:50 by jfleisch          #+#    #+#             */
/*   Updated: 2018/02/21 15:06:17 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strnew(size_t size)
{
	char			*str;

	str = (char*)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}
// char	*ft_strnew(size_t size)
// {
// 	char	*str;
//
// 	if (size == 0)
// 	{
// 		str = (char *)malloc(sizeof(*str) * (1));
// 		if (str)
// 		{
// 			ft_memset(str, '\0', (1));
// 			return (str);
// 		}
// 	}
// 	else if (size)
// 	{
// 		str = (char *)malloc(sizeof(*str) * (size + 1));
// 		if (str)
// 		{
// 			ft_memset(str, '\0', (size + 1));
// 			return (str);
// 		}
// 	}
// 	return (NULL);
// }
