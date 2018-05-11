/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <jfleisch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:43:42 by jfleisch          #+#    #+#             */
/*   Updated: 2018/05/06 15:44:54 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"
#include <stdio.h>

void 				free_map(t_map **map)
{
	size_t			row;

	if (!map)
	{
		ft_putendl("\nfree_map !map");
		return ;
	}
	row = 0;
	while (row < (*map)->size)
		ft_strdel(&((*map)->rows[row++]));
	free((*map)->rows);
	(*map)->rows = NULL;
	(*map)->c = 0;
	(*map)->r = 0;
	free(*map);
	*map = NULL;
}

/*
**	map_empty_map() iterates through the 2d arr map one row at a time
**	creating a new str and setting it to '.'
**	map is freed and the str is deleted if it fails
*/
char				**make_empty_map(size_t size)
{
	char			**map;
	size_t			i;

	if ((map = (char**)ft_memalloc(sizeof(*map) * (size + 1))))
	{
		i = 0;
		while (i < size)
		{
			if (!(map[i] = ft_strnew(size)))
			{
				ft_putendl("\nmake_empty_map !ft_strnew");
				while (--i)
					ft_strdel(&map[i]);
				free(map);
				return (NULL);
			}
			ft_memset(map[i++], '.', size);
		}
	}
	return (map);
}

/*
**	create_map() takes a size (the dim) and sets the map->rows to an empty map
**	if it fails, it frees the map and returns null.
**	it then sets map->size to size
*/
t_map				*create_map(size_t size)
{
	t_map			*map;

	if ((map = (t_map*)ft_memalloc(sizeof(*map))))
	{
		if (!(map->rows = make_empty_map(size)))
		{
			ft_putendl("\ncreate_map !make_empty_map");
			free(map);
			return (NULL);
		}
		map->size = size;
	}
	//ft_putstrarr(map->rows);
	return (map);
}
