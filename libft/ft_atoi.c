/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:04:04 by jfleisch          #+#    #+#             */
/*   Updated: 2018/02/21 17:37:04 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_atoi(const char *str)
{
	long int		i;
	long int		nbr;
	long int		sign;

	i = 0;
	nbr = 0;
	sign = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
			|| (str[i] == '\r') || (str[i] == '\f') || (str[i] == '\v'))
		i++;
	if (str[i] == '-')
		sign = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		nbr = 10 * nbr + (str[i] - '0');
		i++;
	}
	if (sign == 1)
		return ((int)(-nbr));
	return (nbr);
}
