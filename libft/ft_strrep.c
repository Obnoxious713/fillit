/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 20:11:00 by jfleisch          #+#    #+#             */
/*   Updated: 2018/04/14 20:11:02 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_strrep(char *str, char ch1, char ch2)
{
	unsigned char	*ptr;

	ptr = (unsigned char*)str;
	while (*ptr)
	{
		if (*ptr == ch1)
			*ptr = ch2;
		ptr++;
	}
	if (*ptr == ch1)
		*ptr = ch2;
}
