/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <jfleisch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:59:10 by jfleisch          #+#    #+#             */
/*   Updated: 2018/05/06 15:59:10 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"
#include <stdio.h>

int				tet_x_shift(t_etris *tetris)
{
	int			x_shift;

	x_shift = 0;
	while ((tetris->shape)[0][x_shift] == '.')
		x_shift++;
	return (x_shift);
}

int				check_tet_max(t_etris *tetris, t_map *map, t_point *point)
{
	if ((point->y + tetris->height <= (int)map->size)
		&& (point->x - tet_x_shift(tetris) + tetris->width <= (int)map->size))
		return (1);
	return (0);
}

int				validate_piece(char *tet, int location, int *sides)
{
	if (tet[location + 1] == '#')
		*sides += 1;
	if (tet[location + 5] == '#')
		*sides += 1;
	if (location > 0)
	{
		if (tet[location - 1] == '#')
			*sides += 1;
	}
	if (location > 4)
	{
		if (tet[location - 5] == '#')
			*sides += 1;
	}
	if (*sides == 6 || *sides == 8)
		return (1);
	return (0);
}

int				tet_check(char *tet, int rd, t_point ***hash, int count)
{
	int			location;
	int			x_max;
	int			sides;

	location = -1;
	x_max = 0;
	sides = 0;
	while (tet[++location])
	{
		if (tet[location] == '#')
		{
			if (validate_piece(tet, location, &sides) != 1 && sides > 8)
				return (invalid_block(hash));
			set_minmax_points(hash, count++, location, &x_max);
		}
		else if (tet[location] == '\n' || tet[location] != '.')
		{
			if ((location + 1) % 5 && !(rd == BUF && location == BUF - 1))
				return (invalid_block(hash));
		}
	}
	if (!(sides == 6 || sides == 8) || count != 4)
		return (invalid_block(hash));
	(*hash)[1]->x = x_max > (*hash)[1]->x ? x_max : (*hash)[1]->x;
	return (1);
}

int				check_tet_fits(t_etris *tetris, t_map *map, t_point *point)
{
	int			x;
	int			y;
	char		**tetris_shape;
	char		**board;

	tetris_shape = tetris->shape;
	board = map->rows;
	if (!(tetris_dim(tetris)))
		return (0);
	if (check_tet_max(tetris, map, point) != 1)
		return (0);
	y = -1;
	while (tetris_shape[++y] != NULL)
	{
		x = -1;
		while (tetris_shape[y][++x] != '\0')
		{
			if (!(board[y + point->y][x - tet_x_shift(tetris) + point->x] == '.'
				|| tetris_shape[y][x] == '.'))
				return (0);
		}
	}
	return (1);
}
