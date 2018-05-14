/* ************************************************************************** */
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

int 			map_next(t_map *map)
{
	int			c;
	int			r;
	int			dim;

	c = map->c;
	r = map->r;
	dim = (int)map->size + 1;
	if (r > dim)
	{
		map->r = 0;
		map->c += 1;
	}
	if (c < dim)
		return (1);
	return (0);
}

void 			tet_place(t_etris *tetris, t_map *map, t_point *first)
{
	int			y;
	int			x;
	char		**board;
	char		**tetris_shape;

	ft_putendl("\n*******TET_PLACE*******\n");
	y = -1;
	board = map->rows;
	tetris_shape = tetris->shape;
	ft_putendl("tetris piece to be placed:");
	ft_putstrarr(tetris->shape);
	printf("\npiece width = %d\npiece height = %d\n", tetris->width, tetris->height);
	printf("map size = %zu\n", map->size);
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
	ft_putendl("\nthe board after the piece is placed");
	ft_putstrarr(map->rows);
	ft_putendl("");
	first->y = map->c;
	first->x = map->r;
}

void 			tet_remove(t_etris *tetris, t_map *map, t_point *first)
{
	int			r;
	int			c;
	int			id;
	int			i;
	char		**board;

	ft_putendl("\n*******TET_REMOVE*******\n");
	c = -1;
	i = -1;
	id = 0;
	board = map->rows;
	while (tetris->shape[0][++i] == '.')
		;
	id = tetris->shape[0][i];
	printf("tetris id to be removed = %d\n", id);
	while (board[++c] != NULL)
	{
		r = -1;
		while (board[c][++r] != '\0')
		{
			if (board[c][r] == id)
				board[c][r] = '.';
		}
	}
	ft_putendl("\nthe board after the piece is removed");
	ft_putstrarr(map->rows);
	ft_putendl("\n\n");
	map->c = first->y;
	map->r = first->x + 1;
}

int			solve(t_list **pieces, t_map *map, t_point *first)
{
	int		dim;

	ft_putendl("\n*******SOLVE*******\n");
	if (!pieces || !*pieces)
		return (1);
	dim = (int)map->size - 1;
	printf("zero based dimensions of the board = %d x %d\n", dim, dim);
	while (map->c < dim)
	{
		printf("the boards current y axis location map->c = %d\n", map->c);
		map->r = 0;
		while (map->r < dim)
		{
			printf("the boards current x axis location map->r = %d\n", map->r);
			if (check_tet_fits((t_etris*)(*pieces)->cont, map))
			{
				tet_place((t_etris*)(*pieces)->cont, map, first);
				map->r = 0;
				map->c = 0;
				if (solve(&((*pieces)->next), map, first))
					return (1);
				tet_remove((t_etris*)(*pieces)->cont, map, first);
				map_next(map);
			}
			map->r++;
		}
		map->c++;
	}
	return (0);
}
