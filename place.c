/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <jfleisch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:43:30 by jfleisch          #+#    #+#             */
/*   Updated: 2018/05/06 15:46:10 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"
#include <stdio.h>

// void 			free_tetris(t_etris *tetris)
// {
//
// }

int 			tet_place(t_etris* tetris, t_map *map, t_point *first, int count)
{
	int			y;
	int			x;
	char		**board;
	char		**tetris_shape;

	y = -1;
	board = map->rows;
	tetris_shape = tetris->shape;
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
	first->y = map->c;
	first->x = map->r;
	return (count);
}

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

void 			tet_remove(t_list **pieces, t_map *map, int count, t_point *first)
{
	int			r;
	int			c;
	char		**board;

	c = -1;
	board = map->rows;
	while (board[++c] != NULL)
	{
		r = -1;
		while (board[c][++r] != '\0')
		{
			ft_strrep(board[c], count + 'A', '.');
			// if (board[c][r] == ())
			// 	board[c][r] = '.';
		}
	}
	(*pieces)->prev = *pieces;
	map->c = first->y;
	map->r = first->x + 1;
	map_next(map);
}
