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

char			**shape_piece(int height, int width)
{
	char		**shape;
	int			i;

	i = 0;
	if ((shape = (char**)ft_memalloc(sizeof(*shape) * 42)))
	{
		shape[i] = (char*)ft_memalloc(sizeof(shape) * width * height);
		while (i < height)
		{
			if (!(shape[i] = ft_strnew(width + 1)))
			{
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

t_etris			*make_piece(char *tet, int id)
{
	t_etris		*tetris;
	t_point		**point;

	// ft_putendl("\n*******MAKE_PIECE*******\n");
	// ft_putendl("the tet that was passed in from the file");
	ft_putendl(tet);
	if (!tet || !(point = (t_point**)ft_memalloc(sizeof(*point) * 42))
		|| !(*point = (t_point*)ft_memalloc(sizeof(point) * 42)))
		return (0);
	point[0][0].x = 0;
	point[0][0].y = 0;
	point[0][1].x = 0;
	point[0][1].y = 0;
	if (!(tet_check(tet, 21, point)))
		return (0);
	if ((tetris = (t_etris*)ft_memalloc(sizeof(*tetris))))
	{
		// ft_putendl("the height and width of the unshaped tet passed in from the file");
		tetris->height = (*point[1]).y - (*point[0]).y + 1;
		// printf("tetris->height == (*point[1]).y = %d - (*point[0]).y = %d + 1 == %d\n", (*point[1]).y, (*point[0]).y, (*point[1]).y - (*point[0]).y + 1);
		tetris->width = (*point[1]).x - (*point[0]).x + 1;
		// printf("tetris->width == (*point[1]).x = %d - (*point[0]).x = %d + 1 == %d\n\n", (*point[1]).x, (*point[0]).x, (*point[1]).x - (*point[0]).x + 1);
		tetris->id = id;
		tetris->first = point[0];
		if (!(tetris->shape = shape_piece(tetris->height, tetris->width)))
			return (0);
		// printf("\ntet height = %d\ntet width = %d\ntet id = %d\n", tetris->height, tetris->width, tetris->id);
		// printf("tet first x = %d\ntet first y = %d\n\n", tetris->first->x, tetris->first->y);
		// ft_putendl("the return from shape_piece currently stored in tetris->shape");
		// ft_putstrarr(tetris->shape);
		fill_piece(tet, id, tetris);
		// ft_putendl("\nthe filled tetris piece to be stored in the list:");
		// ft_putstrarr(tetris->shape);
		// ft_putendl("");
		point[0][0].x = 0;
		point[0][0].y = 0;
		point[0][1].x = 0;
		point[0][1].y = 0;
		tet_to_tetris(tetris, point);
		// ft_putendl("the NEW height and width of the SHAPED tetris piece");
		tetris->height = (*point[1]).y;
		// printf("NEW tetris height == (*point[1]).y = %d\n", (*point[1]).y);
		tetris->width = (*point[1]).x;
		// printf("NEW tetris width == (*point[1]).x = %d\n\n", (*point[1]).x);
		tetris->id = id;
		// printf("'NEW' tetris id = %d\n", tetris->id);
		tetris->first = point[0];
		// printf("NEW tetris first y = %d\ntetris first x = %d\n\n", tetris->first->y, tetris->first->x);
		tetris->last = point[1];
		// printf("NEW tetris last y = %d\ntetris last x = %d\n\n", tetris->last->y, tetris->last->x);
	}
	return (tetris);
}
