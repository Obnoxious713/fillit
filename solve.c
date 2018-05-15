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

int					invalid_block(t_point ***points)
{
	free_minmax_points(points);
	return (0);
}

void				tet_place(t_etris *tetris, t_map *map, t_point *first)
{
	int				y;
	int				x;
	char			**board;
	char			**tetris_shape;

	y = -1;
	tetris->first = create_point(0);
	tetris->first = create_point(0);
	board = map->rows;
	tetris_shape = tetris->shape;
	while (tetris_shape[++y] != NULL)
	{
		x = -1;
		while (tetris_shape[y][++x] != '\0')
		{
			if (tetris_shape[y][x] != '.')
			{
				board[first->y + y][first->x - tet_x_shift(tetris) +
				x] = tetris_shape[y][x];
			}
		}
	}
	tetris->first->y = first->y;
	tetris->first->x = (first->x) - tet_x_shift(tetris);
}

void				tet_remove(t_etris *tetris, t_map *map)
{
	int				r;
	int				c;
	char			**board;

	c = -1;
	board = map->rows;
	while (tetris->shape[++c] != NULL)
	{
		r = -1;
		while (tetris->shape[c][++r] != '\0')
		{
			if (tetris->shape[c][r] != '.')
				board[c + tetris->first->y][r + tetris->first->x] = '.';
		}
	}
}

int					solve(t_list **pieces, t_map *map, t_point *first)
{
	int				fit;

	if (!pieces || !*pieces)
		return (1);
	while ((!(fit = check_tet_fits((t_etris*)(*pieces)->cont, map, first))
			&& get_next_point(&first, map->rows)))
		;
	if (!fit)
		return (0);
	tet_place((t_etris*)(*pieces)->cont, map, first);
	if (!solve(&((*pieces)->next), map, create_point(0)))
	{
		tet_remove((t_etris*)(*pieces)->cont, map);
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
