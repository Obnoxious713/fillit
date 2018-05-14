point/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <jfleisch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:42:36 by jfleisch          #+#    #+#             */
/*   Updated: 2018/05/06 15:46:26 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"
#include <stdio.h>

void 			map_next(t_map *map)
{
	int			dim;

	dim = (int)map->size - 1;
	if (map->r < dim)
		map->r++;
	else
	{
		map->r = 0;
		map->c += 1;
	}
}

void 			tet_place(t_etris *tetris, t_map *map, t_point *point)
{
	int			y;
	int			x;
	char		**board;
	char		**tetris_shape;

	// ft_putendl("\n*******TET_PLACE*******\n");
	y = -1;
	board = map->rows;
	tetris_shape = tetris->shape;
	// ft_putendl("tetris piece to be placed:");
	// ft_putstrarr(tetris->shape);
	//printf("\npiece width = %d\npiece height = %d\n", tetris->width, tetris->height);
	// printf("map size = %zu\n", map->size);
	while (tetris_shape[++y] != NULL)
	{
		x = -1;
		while (tetris_shape[y][++x] != '\0')
		{
			if (tetris_shape[y][x] != '.')
			{
				board[map->c + y][map->r + x]
				= tetris_shape[y][x];
			}
		}
	}
	// ft_putendl("\nthe board after the piece is placed");
	ft_putstrarr(map->rows);
	ft_putendl("");
	point->y = (map->c + y);
	point->x = (map->r + x);
	tetris->first[0]->x
	// printf("tet point x = %d\ntet point y = %d\n\n", point->x, point->y);
}

void 			tet_remove(t_etris *tetris, t_map *map, t_point *point)
{
	int			r;
	int			c;
	int			id;
	int			i;
	char		**board;

	// ft_putendl("\n*******TET_REMOVE*******\n");
	c = -1;
	i = -1;
	id = 0;
	board = map->rows;
	while (tetris->shape[0][++i] == '.')
		;
	id = tetris->shape[0][i];
	// printf("tetris id to be removed = %d\n", id);
	while (board[++c] != NULL)
	{
		r = -1;
		while (board[c][++r] != '\0')
		{
			if (board[c][r] == id)
				board[c][r] = '.';
		}
	}
	// ft_putendl("\nthe board after the piece is removed");
	// ft_putstrarr(map->rows);
	// ft_putendl("\n\n");
	if (point->x < (int)map->size - 1)
	{
		map->r = point->x + 1;
		map->c = point->y;
	}
	else
	{
		map->r = point->x;
		map->c = point->y + 1;
	}
	map_next(map);
}

int			solve(t_list **pieces, t_map *map, t_point *point)
{
	int		dim;

	// ft_putendl("\n*******SOLVE*******\n");
	if (!pieces || !*pieces)
		return (1);
	dim = (int)map->size - 1;
	// printf("zero based dimensions of the board = %d x %d\n", dim, dim);
	while (map->c <= dim)
	{
		// printf("the boards current y axis location map->c = %d\n", map->c);
		map->r = 0;
		while (map->r <= dim)
		{
			// printf("the boards current x axis location map->r = %d\n", map->r);
			if (check_tet_fits((t_etris*)(*pieces)->cont, map))
			{
				tet_place((t_etris*)(*pieces)->cont, map, point);
				map->r = 0;
				map->c = 0;
				if (solve(&((*pieces)->next), map, point))
					return (1);
				tet_remove((t_etris*)(*pieces)->cont, map, point);
			}
			map->r++;
		}
		map->c++;
	}
	return (0);
}
