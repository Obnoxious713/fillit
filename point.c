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

int					next_point(t_point **first, t_map *map)
{
	int				fc;
	int				fr;
	char			**board;

	fc = (*first)->y;
	fr = (*first)->x;
	board = map->rows;
	fr += 1;
	while (board[fc] != NULL)
	{
		while (board[fc][fr] != '\0')
		{
			if (board[fc][fr] == '.')
				return (1);
			fr += 1;
		}
		fc += 1;
		fr = 0;
	}
	return (0);
}

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
	if (count == 0 || count == 3)
		(*point)[count == 0 ? 0 : 1] = create_point(location);
	else if ((int)(location % 5) < (*point)[0]->x)
		(*point)[0]->x = location % 5;
}

int			invalid_block(t_point ***points)
{
	free_minmax_points(points);
	return (0);
}

void 				free_point(t_point **point)
{
	if (!point)
		return ;
	free(*point);
	*point = NULL;
}

void 				free_minmax_points(t_point ***points)
{
	if (!points)
		return ;
	free_point(*points + 1);
	free_point(*points);
	free(*points);
	*points = NULL;
}
