/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <jfleisch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 13:15:42 by jfleisch          #+#    #+#             */
/*   Updated: 2018/05/06 15:45:35 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "fillit.h"
#include "libft/libft.h"
#include <stdio.h>

static int			error_ret(int flag)
{
	if (!flag)
		ft_putendl("\nerror");
	else if (flag == 3)
		ft_putendl("\n!pieces = read_file");
	else if (flag == 2)
		ft_putendl("\nincorrect number of args");
	else if (flag == 0)
		ft_putendl("\ninvalid file");
	else if (flag == -1)
		ft_putendl("\ncould not open file");
	if (flag && flag != 1)
		ft_putendl("\nusage: fillit [input_file]");
	return (flag);
}

t_list				*read_file(t_list **pieces, int file)
{
	int				rd;
	int				p_nbr;
	char			tet[BUF * 4];
	t_list			*start;
	t_list			*end;

	p_nbr = 0;
	pieces = (t_list**)ft_memalloc(sizeof(*pieces) * 27);
	pieces[p_nbr] = (t_list*)ft_memalloc(sizeof(pieces) * 27);
	start = pieces[0];
	end = pieces[p_nbr];
	while ((rd = read(file, tet, BUF)) == BUF)
	{
		tet[BUF - 1] = 0;
		if (p_nbr >= 26	|| (!(tet_lstadd(&start, &end, tet, p_nbr) == 1)))
			return (0);
		p_nbr++;
	}
	if (rd == BUF - 1)// EOF
	{
		if (p_nbr >= 26	|| (!(tet_lstadd(&start, &end, tet, p_nbr) == 1)))
			return (0);
		p_nbr++;
	}
	else
		return (0);
	return (start);
}

void 				reset_pieces(t_list **pieces)
{
	while (*pieces)
	{
		(*pieces)->first->x = 0;
		(*pieces)->first->y = 0;
		(*pieces)->last->x = 0;
		(*pieces)->last->y = 0;
	}
}

int					main(int ac, char **av)
{
	int				file;
	t_list			*pieces;
	t_map			*map;
	t_point			*point;
	size_t			map_size;
	t_list			*lst_tail;

	if (ac == 2)
	{
		ft_putendl("");
		ft_putendl("       ***********************************************");
		ft_putendl("*************************************************************");
		ft_putendl("       ***********************************************");
		ft_putendl("");
		map_size = 2;
		if (!(map = create_map(map_size)))
			return (0);
		if(!(point = (t_point*)ft_memalloc(sizeof(*point) * 42)))
			return (0);
		(*point).x = 0;
		(*point).y = 0;
		if (!(file = open(av[1], O_RDONLY)))
			return (error_ret(-1));
		if (!(pieces = read_file(&pieces, file)))
		{
			close(file);
			return (0);
		}
		while ((lst_tail = pieces) && !(solve(&pieces, map, point)))
		{
			free_map(&map);
			map = create_map(map_size++);
			point->y = 0;
			point->x = 0;
			reset_pieces(pieces)
		}
		ft_putstrarr(map->rows);
	}
	else
		return (error_ret(0));
	return (1);
}
