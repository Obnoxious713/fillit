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

// void 			free_tetris(t_etris *tetris)
// {
//
// }

/*
**	part of problem
**		when the map isn't reset and the same piece is placed again
**			count still increases
*/
//
// int 			map_next(t_map *map)
// {
// 	int			c;
// 	int			r;
// 	int			dim;
//
// 	c = map->c;
// 	r = map->r;
// 	dim = (int)map->size + 1;
// 	if (r > dim)
// 	{
// 		map->r = 0;
// 		map->c += 1;
// 	}
// 	if (c < dim)
// 		return (1);
// 	return (0);
// }

void 			tet_place(t_etris *tetris, t_map *map, t_point *first)
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
	ft_putendl("\nafter tet_place");
	ft_putstrarr(map->rows);
	ft_putendl("");
	tetris.first->y = map->c + y;
	tetris.first->y = map->r + x
}

void 			tet_remove(t_etris *tetris, t_map *map, t_point *first)
{
	int			r;
	int			c;
	int			id;
	int			i;
	char		**board;

	c = -1;
	i = 0;
	id = 0;
	board = map->rows;
	while (tetris->shape[0][i] == '.')
		i++;
	id = tetris->shape[0][i + 1];
	printf("%d\n", id);
	while (board[++c] != NULL)
	{
		r = -1;
		while (board[c][++r] != '\0')
		{
			if (board[c][r] == id)
				board[c][r] = '.';
		}
	}
	ft_putendl("\nafter tet_remove");
	ft_putstrarr(map->rows);
	ft_putendl("\n\n");
	map->c = first->y;
	map->r = first->x + 1;
}

int			solve(t_list **pieces, t_map *map, t_point *first)
{
	int		i;
	int		dim;

	i = -1;
	dim = (int)map->size - 1;
	if (*pieces == NULL)
		return (1);
	while (map->c < dim)
	{
		map->r = 0;
		while (map->r < dim)
		{
			if (check_tet_fits((t_etris*)(*pieces)->cont, map))//, first))
			{
				tet_place((t_etris*)(*pieces)->cont, map, first);
				if (!(solve(&((*pieces)->next), map, first)))
					tet_remove((t_etris*)(*pieces)->cont, map, first);
				else
					return (1);
			}
			map->r++;
		}
		map->c++;
	}
	return (0);
}
