/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <jfleisch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:43:18 by jfleisch          #+#    #+#             */
/*   Updated: 2018/05/06 15:45:52 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"
#include <stdio.h>

/*
**	fill_piece() iterates through each row of tet and shape placing the '#'
**	in the correct spot and then sets the '#' to the correct id
*/
void 			fill_piece(char *tet, char id, t_etris *tetris)
{
	int 				x;
	int					y;

	y = -1;
	x = tetris->first->x + tetris->first->y * 5;
	while (++y < tetris->height)
	{
		ft_memcpy(tetris->shape[y], &tet[x], tetris->width);
		ft_strrep(tetris->shape[y], '#', id);
		x += 5;
	}
}

/*
**	shape_piece() creates a grid of '.'	based on the height and width
**	one row at a time and null terminates at the end
*/
char			**shape_piece(int height, int width)
{
	char		**shape;
	int			i;

	i = 0;
	if ((shape = (char**)ft_memalloc(sizeof(*shape) * 42)))
	{
		//shape[i] = (char*)ft_memalloc(sizeof(shape) * width * height);
		while (i < height)
		{
			if (!(shape[i] = ft_strnew(width + 1)))
			{
				ft_putendl("\nshape_piece !shape[i] = ft_strnew");
				while (--i)
					ft_strdel(&shape[i]);
				return (0);
			}
			ft_memset(shape[i++], '.', width);
		}
		shape[i] = 0;
	}
	return (shape);
}

/*
**	make_piece() sets the pieces x and y pos
**	then sets the piece width, height, first pos, and shape
**	it then fills the shape with the correct id letter
**	it then frees the pos once it's done
*/
t_etris			*make_piece(char *tet, int id)
{
	t_etris		*tetris;
	t_point		**point;

	if (!tet || !(point = (t_point**)ft_memalloc(sizeof(*point) * 777))
		|| !(*point = (t_point*)ft_memalloc(sizeof(point) * 777)))
	{
		ft_putendl("\nmake_piece !tet || !point malloc");
		return (0);
	}
	(point[0][0]).x = 0;
	(point[0][0]).y = 0;
	(point[0][1]).x = 0;
	(point[0][1]).y = 0;

	if (!(tet_check(tet, 21, point)))
	{
		ft_putendl("\nmake_piece !tet_check");
		return (0);
	}
	//printf("\nmake_piece sides = %d\n", (*point)->sides);
	if ((tetris = (t_etris*)ft_memalloc(sizeof(*tetris))))
	{
		tetris->height = (*point[1]).y - (*point[0]).y + 1;
		tetris->width = (*point[1]).x - (*point[0]).x + 1;
		tetris->first = point[0];
		if (!(tetris->shape = shape_piece(tetris->height, tetris->width)))
		{
			ft_putendl("\nmake_piece !shape_piece");
			return (0);
		}
		fill_piece(tet, id, tetris);
	}
	return (tetris);
}
