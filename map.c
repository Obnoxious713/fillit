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
		return ;
	row = 0;
	while (row < (*map)->size)
		ft_strdel(&((*map)->rows[row++]));
	free((*map)->rows);
	(*map)->rows = NULL;
	free(*map);
	*map = NULL;
}

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

t_map				*create_map(size_t size)
{
	t_map			*map;

	if ((map = (t_map*)ft_memalloc(sizeof(*map))))
	{
		if (!(map->rows = make_empty_map(size)) && !(map->save = map->rows))
		{
			free(map);
			return (0);
		}
		map->size = size;
	}
	return (map);
}
