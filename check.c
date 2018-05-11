/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <jfleisch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:59:10 by jfleisch          #+#    #+#             */
/*   Updated: 2018/05/06 15:59:10 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"
#include <stdio.h>

/*
**	check_tet_fits() iterates through the tetris shape checking if
**
*/
int				check_tet_fits(t_etris *tetris, t_map *map)
{
	int			y;
	int			x;
	int			c;
	int			r;
	int			safe;

	safe = 0;
	y = -1;
	r = map->r;
	c = map->c;
	//ft_putstrarr(tetris->shape);
	while (tetris->shape[++y] != NULL)
	{
		//printf("\nctf y = %d\n\n", y);
		x = -1;
		while (tetris->shape[y][++x] != '\0')
		{
			//printf("\nctf x = %d\n\n", x);
			if (tetris->shape[y][x] != '.')
			{
				if (check_safe(map, y, x))
				{
					//ft_putendl("\nsafe");
					safe++;
				}
				else
				{
				//	ft_putendl("\ncheck_tet_fits !check_safe");
					return (0);
				}
			}
		}
	}
	if (safe == 4)
		return (1);
	return (0);
}

/*
**	check_safe() checks the map location and if it is a '.' returns (1)
**	if the x pos is the same as the map dim it returns (2)
**	returns (0) if it's not safe
*/
int				check_safe(t_map *map, int y, int x)
{
	int			c;
	int			r;

	c = map->c;
	r = map->r;
	//printf("c = %d\n\nr = %d\n\n\ny = %d\n\nx = %d\n\n\n\n", c, r, y, x);
//	printf("%d\n", (int)map->size);
	if (c + y < (int)map->size)
	{
		if (map->rows[c + y][r + x] == '.')
			return (1);
	}
	//ft_putendl("check_safe return 0");
	return (0);
}

/*
**	validate_piece() counts and returns the number of hash->sides that a '#' touches
**	+1 right, -1 left, +5 down, -5 up
*/
int					validate_piece(char *tet, int location, int	*sides)
{
	if (tet[location + 1] == '#')
		*sides += 1;
	if (tet[location + 5] == '#')
		*sides += 1;
	if (location > 0)
	{
		if (tet[location - 1] == '#')
			*sides += 1;
	}
	if (location > 4)
	{
		if (tet[location - 5] == '#')
			*sides += 1;
	}
	if (*sides == 6 || *sides == 8)
		return (1);
	return (0);
}

/*
**	tet_check() takes the null terminated string and iterates through it
**	checking that it only contains 4 '#', '.', and '\n'
**	for newlines it checks to see if it's the EOF and returns 0 if not
*/
int					tet_check(char *tet, int rd, t_point **hash)
{
	int				location;
	int				count;
	int				x_max;
	int				sides;

	location = -1;
	count = 0;
	x_max = 0;
	sides = 0;
	while (tet[++location])
	{
		if (tet[location] == '#')
		{
			if (validate_piece(tet, location, &sides) != 1 && sides > 8)
			{
				ft_putendl("\ntet_check !validate_piece");
				return (0);
			}
			set_minmax_points(hash, count, location, x_max);
			count++;
		}
		else if (tet[location] == '\n')
		{
			if ((location + 1) % 5 && !(rd == BUF && location == BUF -1))
			{
				ft_putendl("\ntet_check != '\\n'");
				return (0);
			}
		}
		else if (tet[location] != '.')
		{
			ft_putendl("\ntet_check != '.'");
			return (0);
		}
	}
	//printf("\ncount = %d\n", count);
	if (count != 4)
	{
		ft_putendl("\ntet_check count != 4");

		return (0);
	}
	if (sides == 6 || sides == 8)
	{
		//ft_putendl("\ntet_check sides == 6 || sides == 8");
		return (1);
	}
	return (0);
}
