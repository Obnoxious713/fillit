/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <jfleisch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:42:43 by jfleisch          #+#    #+#             */
/*   Updated: 2018/05/06 15:46:17 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"
#include <stdio.h>

/*
**	create_point() takes the x location and sets it to x % 5
**	and set the y location to (len + 5) / 5 and then subtracts 1 if y is > 0
*/
t_point				*create_point(int location)
{
	t_point			*point;

	if ((point = (t_point*)ft_memalloc(sizeof(*point) * 42)))
	{
		point->x = location % 5;
		point->y = (location + 5) / 5;
		if (point->y > 0)
			point->y -= 1;
	}
	return (point);
}

void 	set_minmax_points(t_point ***point, int count, int location, int *x_max)
{
	*x_max = (int)(location % 5) > *x_max ? (int)(location % 5) : *x_max;
//	printf("\nset_minmax_points x_max = %d\n\n", *x_max);
	if (count == 0 || count == 3)
		(*point)[count == 0 ? 0 : 1] = create_point(location);
	else if ((int)(location % 5) < (*point)[0]->x)
		(*point)[0]->x = location % 5;
	//printf("\nset_minmax_points point[0]->y = %d\nset_minmax_points point[0]->x = %d\n\n", (*point)[0]->y, (*point)[0]->x);
}
