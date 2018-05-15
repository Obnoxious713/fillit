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

int				tetris_dim(t_etris *tetris)
{
	int			x;
	int			y;
	char		**tetris_shape;

	tetris_shape = tetris->shape;
	y = 0;
	while (tetris_shape[y] != NULL)
	{
		x = 0;
		while (tetris_shape[y][x] != '\0')
		{
			x++;
		}
		y++;
	}
	tetris->width = x;
	tetris->height = y;
	return (1);
}

void 			tet_place(t_etris *tetris, t_map *map, t_point *first)
{
	int			y;
	int			x;
	char		**board;
	char		**tetris_shape;

	ft_putendl("\n*******TET_PLACE*******\n");
	y = -1;
	tetris->first = create_point(0);
	tetris->first = create_point(0);
	board = map->rows;
	tetris_shape = tetris->shape;
	ft_putendl("tetris piece to be placed:");
	ft_putstrarr(tetris->shape);
	printf("map size = %zu\n", map->size);
	while (tetris_shape[++y] != NULL)
	{
		x = -1;
		while (tetris_shape[y][++x] != '\0')
		{
			if (tetris_shape[y][x] != '.')
			{
				board[first->y + y][first->x - tet_x_shift(tetris) + x]
				= tetris_shape[y][x];
			}
		}
	}
	ft_putendl("\nthe board after the piece is placed");
	ft_putstrarr(map->rows);
	ft_putendl("");
	tetris->first->y = first->y;
	tetris->first->x = (first->x) - tet_x_shift(tetris);
	printf("tetris->first->y == first->y = %d == %d\n", first->y, tetris->first->y);
	printf("tetris->first->x == first->x - tet_x_shift(tetris) = %d - %d == %d\n\n", first->x, tetris->first->x, first->x - tet_x_shift(tetris));
	// printf("first->y == map->c + y = %d + %d = %d\n", map->c, y, map->c + y);
	// printf("first->x = map->r + x = %d + %d = %d\n\n", map->r, x, map->r + x);
}

void 			tet_remove(t_etris *tetris, t_map *map, t_point *first)
{
	int			r;
	int			c;
	int			id;
	int			i;
	char		**board;
	int			p;

	p = 0;
	if (first != first + 1)
		p++;
	ft_putendl("\n*******TET_REMOVE*******\n");
	c = -1;
	i = -1;
	id = 0;
	board = map->rows;
	while (tetris->shape[0][++i] == '.')
		;
	id = tetris->shape[0][i];
	// printf("tetris id to be removed = %d\n", id);
	while (tetris->shape[++c] != NULL)
	{
		r = -1;
		while (tetris->shape[c][++r] != '\0')
		{
			if (tetris->shape[c][r] != '.')
				board[c + tetris->first->y][r + tetris->first->x] = '.';
		}
	}
	ft_putendl("\nthe board after the piece is removed");
	ft_putstrarr(map->rows);
	ft_putendl("\n\n");
}

int			solve(t_list **pieces, t_map *map, t_point *first)
{
	int			found;

	ft_putendl("\n*******SOLVE*******\n");
	if (!pieces || !*pieces)
		return (1);
	while ((!(found = check_tet_fits((t_etris*)(*pieces)->cont, map, first))
	 		&& get_next_point(&first, map->rows)))
		;
	if (!found)
		return (0);
	tet_place((t_etris*)(*pieces)->cont, map, first);
	if (!solve(&((*pieces)->next), map, create_point(0)))
	{
		tet_remove((t_etris*)(*pieces)->cont, map, first);
		if (!(get_next_point(&first, map->rows)))
		{
			first->y = 0;
			first->x = 0;
			return (0);
		}
		return (solve(pieces, map, first));
	}
	return (1);
}

int					map_solve(t_list **pieces)
{
	t_list			*lst_tail;
	t_map			*map;
	t_point			*first;
	size_t			map_size;

	map_size = 2;
	if (!(map = create_map(map_size)))
		return (0);
	if (!(first = create_point(0)))
		return (0);
	while ((lst_tail = *pieces) && !(solve(&lst_tail, map, first)))
	{
		free_map(&map);
		if (!(map = create_map(++map_size)))
			return (0);
		first->y = 0;
		first->x = 0;
	}
	ft_putstrarr(map->rows);
	free_map(&map);
	free(map);
	return (1);
}
