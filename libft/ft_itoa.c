/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:16:17 by jfleisch          #+#    #+#             */
/*   Updated: 2018/02/21 15:16:32 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			count_digits(int n)
{
	int				i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int			is_neg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

static int			ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char				*ft_itoa(int n)
{
	int				len;
	int				neg;
	char			*res;

	neg = is_neg(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (neg)
		n = -n;
	len = neg + count_digits(n);
	res = ft_strnew(len);
	if (!res)
		return (NULL);
	while (len--)
	{
		res[len] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	if (neg)
		res[0] = '-';
	return (res);
}
