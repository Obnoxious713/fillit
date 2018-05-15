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
		ft_putendl("\n!pieces = read_file\nvalid file contains 2 --> 26 tetriminos");
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
	char			tet[BUF + 1];
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

int					main(int ac, char **av)
{
	int				file;
	t_list			*pieces;

	if (ac == 2)
	{
		if (!(file = open(av[1], O_RDONLY)))
			return (error_ret(-1));
		ft_putendl("");
		ft_putendl("       ***********************************************");
		ft_putendl("*************************************************************");
		ft_putendl("       ***********************************************");
		ft_putendl("");
		if (!(pieces = read_file(&pieces, file)))
		{
			close(file);
			return (error_ret(3));
		}
		if (!map_solve(&pieces))
			return (0);
	}
	else
		return (error_ret(0));
	return (1);
}
