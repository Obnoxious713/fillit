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

/*
**	error_ret() takes a flag (-1, 0, 1, 2) and prints the error accordingly
**	if none of those flags are passed it prints error
*/
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
	{
		ft_putendl("\nusage: fillit [input_file]");
		ft_putendl("	input_file:");
		ft_putendl("		- contains between 1 and 26 tetriminos");
		ft_putendl("		- exactly 4 lines of 4 chars and a newline");
		ft_putendl("		- '#', '.', '\\n' only");
		ft_putendl("		- '\\n' following each tetrimino unless EOF");
		ft_putendl("		- each '#' must touch another on at least 1 side");
	}
	return (flag);
}


/*
**	read_file() reads the file 21 characters at a time
**	it then null terminates the string by setting the 21st char to 0
**	it checks that there are no more than 26 pieces being passed in,
**	that each piece is a valid tetrimino,
**	and then tries to add that piece to a list
**	if read reaches the EOF then it stores the final tetrimino and calls solve
*/
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
		{
			ft_putendl("\nread_file p_nbr >= 26 || !pieces[p_nbr] = tet_lstadd");
			return (0);
		}
		p_nbr++;
	}
	if (rd == BUF - 1)// EOF
	{
		if (p_nbr >= 26	|| (!(tet_lstadd(&start, &end, tet, p_nbr) == 1)))
		{
			ft_putendl("\nread_file p_nbr >= 26 || !pieces[p_nbr] = tet_lstadd");
			return (0);
		}
		p_nbr++;
	}
	else
	{
		ft_putendl("\nread_file else called");
		return (0);
	}
	return (start);
}

/*
**	main() checks for 1 arg (ac == 2) and returns an error if it's false
**	if it's true attempts to open the file and pass it into read_file to be read
*/
int					main(int ac, char **av)
{
	int				file;
	t_list			*pieces;
	t_map			*map;
	size_t			map_size;


	if (ac == 2)
	{
		map_size = 2;
		if (!(map = create_map(map_size)))
		{
			ft_putendl("\nsetup_solve !map");
			return (0);
		}
		(*map).r = 0;
		(*map).c = 0;
		if (!(file = open(av[1], O_RDONLY)))
		{
			ft_putendl("\nmain !file = open");
			return (error_ret(-1));
		}
		if (!(pieces = read_file(&pieces, file)))
		{
			ft_putendl("\nmain !pieces = read_file");
			close(file);
			return (0);
		}
		while (!(setup_solve(&pieces, map)))
		{
			printf("map_size = %d\n", (int)(map_size));
			free_map(&map);
			map = create_map(map_size++);

		}
		ft_putstrarr(map->rows);
	}
	else
		return (error_ret(0));
	return (1);
}
