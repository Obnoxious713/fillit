/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrarr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 19:54:07 by jfleisch          #+#    #+#             */
/*   Updated: 2018/04/14 19:54:09 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putstrarr(char **strarr)
{
	size_t		i;

	i = 0;
	if (strarr)
	{
		while (strarr[i] != NULL)
		{
			ft_putstr(strarr[i]);
			ft_putchar('\n');
			i++;
		}
	}
}
