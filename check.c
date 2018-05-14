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

int				check_tet_fits(t_etris *tetris, t_map *map)
{
	int			y;
	int			x;
	int			c;
	int			r;
	int			safe;

	safe = 0;
	y = -1;
	r = map->r;
	c = map->c;
	ft_putendl("\n*******CHECK_SAFE*******\n");
	while (tetris->shape[++y] != NULL)
	{
		x = -1;
		while (tetris->shape[y][++x] != '\0')
		{
			if (tetris->shape[y][x] != '.')
			{
				if (check_safe(map, y, x))
					safe++;
				else
					return (0);
			}
		}
	}
	if (safe == 4)
	{
		ft_putendl("piece is safe to place");
		return (1);
	}
	ft_putendl("piece is not placeable here");
	return (0);
}

int				check_safe(t_map *map, int y, int x)
{
	if (map->c + y < (int)map->size)
	{
		printf("map->c = %d\nmap->r = %d\n", map->c, map->r);
		printf("y = %d\nx = %d\n", y, x);
		printf("the location that is being checked:\nmap->rows[%d][%d] = '%c'\n", (map->c + y), (map->r + x), map->rows[map->c + y][map->r + x]);
		if (map->rows[map->c + y][map->r + x] == '.')
		{
			ft_putendl("safe\n\n");
			return (1);
		}
		ft_putendl("not safe\n\n");
	}
	return (0);
}

int					tet_x_shift(t_etris *tetris)
{
	int				x_shift;

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

int					validate_piece(char *tet, int location, int	*sides)
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

void 	reset_minmax_points(t_point ***point, int count, int y, int x, int *y_max, int *x_max)
{
	// ft_putendl("\n*******RESET_MINMAX_POINTS*******\n");
	*y_max = (int)(y) > *y_max ? (int)(y) : *y_max;
	*x_max = (int)(x) > *x_max ? (int)(x) : *x_max;
	if (count == 0 || count == 3)
	{
		(*point)[count == 0 ? 0 : 1]->y = *y_max;
		(*point)[count == 0 ? 0 : 1]->x = *x_max;
	}
	else
	{
			if ((int)(y) < (*point)[0]->y)
				(*point)[0]->y = y;
			else if ((int)(x) < (*point)[0]->x)
				(*point)[0]->x = x;
	}
	// printf("(*point)[0]->y = %d\n(*point)[0]->x = %d\n(*point)[1]->y = %d\n(*point)[1]->x = %d\n\n", (*point)[0]->y, (*point)[0]->x, (*point)[1]->y, (*point)[1]->x);
}

int					tet_to_tetris(t_etris *tetris, t_point **hash)
{
	int				y;
	int				x;
	int				count;
	int				y_max;
	int				x_max;

	// ft_putendl("\n*******TET_TO_TETRIS*******\n");
	y = -1;
	count = 0;
	y_max = 0;
	x_max = 0;
	while (tetris->shape[++y] != NULL)
	{
		x = -1;
		while (tetris->shape[y][++x] != '\0')
		{
			if (tetris->shape[y][x] == tetris->id)
			{
				reset_minmax_points(&hash, count, y, x, &y_max, &x_max);
				count++;
			}
			else if (tetris->shape[y][x] != '.')
				return (0);
		}
	}
	if (count != 4)
		return (0);
	return (1);
}

int					tet_check(char *tet, int rd, t_point **hash)
{
	int				location;
	int				count;
	int				x_max;
	int				sides;

	//ft_putendl("\n*******TET_CHECK*******\n");
	location = -1;
	count = 0;
	x_max = 0;
	sides = 0;
	while (tet[++location])
	{
		if (tet[location] == '#')
		{
			if (validate_piece(tet, location, &sides) != 1 && sides > 8)
				return (0);
			set_minmax_points(&hash, count, location, &x_max);
			count++;
		}
		else if (tet[location] == '\n')
		{
			if ((location + 1) % 5 && !(rd == BUF && location == BUF -1))
				return (0);
		}
		else if (tet[location] != '.')
			return (0);
	}
	if (count != 4)
		return (0);
	if (sides == 6 || sides == 8)
	{
		(hash[1])->x = x_max > (hash[1])->x ? x_max : (hash[1])->x;
		// printf("(*hash)[1]->x = %d\n", (hash[1])->x);
		return (1);
	}
	return (0);
}
