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

int						setup_solve(t_list **pieces, t_map *map, int count)
{
	int					dim;

	dim = (int)map->size - 1;
	if ((*pieces) == NULL)
	{
		ft_putendl("\netup_solve (*pieces) ==  NULL\n");
		return (1);
	}
	while (map->c < dim)
	{
		map->r = 0;
		while (map->r < dim)
		{
			// ft_putendl("setup solve list_elem");
			// ft_putstrarr(((t_etris*)(*pieces)->cont)->shape);
			// ft_putendl("\n");
			if (check_tet_fits((t_etris*)(*pieces)->cont, map))
			{
				tet_place((t_etris*)(*pieces)->cont, map);
				count++;
				// ft_putstrarr(map->rows);
				// ft_putendl("\n");
				if (setup_solve(&((*pieces)->next), map, count))
				{
					//ft_putendl("setup_solve recursion return 1");
					return (1);
				}
				tet_remove(pieces, map, count - 1);
			}
			map->r++;
		}
		map->c++;
	}
	//ft_putendl("setup_solve return 0");
	return (0);
}

// int					solve_map(t_map *map, t_list **pieces)
// {
// 	int				fit;
//
// 	fit = 0;
// 	if (!pieces || !*pieces)
// 	{
// 		ft_putendl("\nsolve_map !pieces || !*pieces");
// 		return (0);
// 	}
// 	while (!(fit = check_tet_fits((t_etris*)(*pieces)->cont, map)))
// 	{
// 		ft_putendl("\nsolve_map !check_tet_fits");
// 		return (0);
// 	}
// 	if (!fit)
// 	{
// 		ft_putendl("\nsolve_map !fit");
// 		return (0);
// 	}
// 	tet_place((t_etris*)(*pieces)->cont, map);
// 	if (!(solve_map(map, &((*pieces)->next))))
// 	{
// 		ft_putendl("\nsolve_map !solve_map: tet_remove called");
// 		tet_remove((t_etris*)(*pieces)->cont, map);
// 		return (solve_map(map, pieces));
// 	}
// 	return (1);
// }
//
// /*
// **	map_solve() is called until (*pieces) is NULL
// **	it calls check_tet_fits and places the tet on the map if it does
// **	it then calls map_solve() again with the next piece
// **	if that fails it removes the last tet
// */
// int					setup_solve(t_list **pieces, t_map *map)
// {
// 	t_list			*last_piece;
// 	size_t			map_size;
//
//
// 	while ((last_piece = *pieces)
// 		&& !(solve_map(map, &last_piece)))
// 	{
// 		free_map(&map);
// 		if (!(map = create_map(++map_size)))
// 		{
// 			ft_putendl("\nsetup_solve !create_map");
// 			return (0);
// 		}
// 	}
// 	ft_putstrarr(map->rows);
// 	free_map(&map);
// 	free(map);
// 	return (1);
// }
