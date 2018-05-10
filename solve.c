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

int					solve_map(t_map *map, t_list **pieces, t_point *point)
{
	int				fit;

	fit = 0;
	if (!pieces || !*pieces)
	{
		ft_putendl("\nsolve_map !pieces || !*pieces");
		return (0);
	}
	while (!(fit = check_tet_fits((t_etris*)(*pieces)->cont, map)))
	{
		ft_putendl("\nsolve_map !check_tet_fits");
		return (0);
	}
	if (!fit)
	{
		ft_putendl("\nsolve_map !fit");
		return (0);
	}
	tet_place((t_etris*)(*pieces)->cont, map, point);
	if (!solve_map(map, &((*pieces)->next), create_point(0)))
	{
		ft_putendl("\nsolve_map !solve_map: tet_remove called");
		tet_remove((t_etris*)(*pieces)->cont, map);
		// if (!get_next_point(&p_start, map->rows))
		// {
		// 	p_start->x = 0;
		// 	p_start->y = 0;
		// 	return (0);
		// }
        //	TODO:
		return (solve_map(map, pieces, point));
	}
	return (1);
}

/*
**	map_solve() is called until (*pieces) is NULL
**	it calls check_tet_fits and places the tet on the map if it does
**	it then calls map_solve() again with the next piece
**	if that fails it removes the last tet
*/
int					setup_solve(t_list **pieces)
{
	t_map			*map;
	t_point			*p_start;
	t_list			*last_piece;
	size_t			map_size;

	map_size = BOARD_SIZE;
	if (!(map = create_map(map_size)))
	{
		ft_putendl("\nsetup_solve !map");
		return (0);
	}
	if (!(p_start = create_point(0)))
	{
		ft_putendl("\nsetup_solve !p_start");
		return (0);
	}
	while ((last_piece = *pieces)
		&& !(solve_map(map, &last_piece, p_start)))
	{
		free_map(&map);
		if (!(map = create_map(++map_size)))
		{
			ft_putendl("\nsetup_solve !map");
			return (0);
		}
		p_start->x = 0;
		p_start->y = 0;
	}
	ft_putstrarr(map->rows);
	free_map(&map);
	free(map);
	return (1);
}

/*
**	solve() calls create map and stores the value in map
**	it then calls map_solve()
*/
int					solve(t_list *pieces)
{
	if (setup_solve(&pieces))
	{
		ft_putendl("\nsolve !setup_solve");
		return (0);
	}
	return (1);
}
