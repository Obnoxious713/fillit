/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:58:53 by jfleisch          #+#    #+#             */
/*   Updated: 2018/02/21 17:53:27 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strstr(const char *hay, const char *need)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (hay[i] == need[i] && hay[i] == '\0')
		return ((char*)&hay[i]);
	while (hay[i])
	{
		j = i;
		while (hay[j] == need[j - i] && hay[j])
			j++;
		if (need[j - i] == '\0')
			return ((char*)&hay[i]);
		i++;
	}
	return (0);
}
