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

t_list				*read_file(t_list **pieces, int file,
								t_list *start, t_list *end)
{
	int				rd;
	int				p_nbr;
	char			tet[BUF + 1];

	p_nbr = 0;
	pieces = (t_list**)ft_memalloc(sizeof(*pieces) * 27);
	pieces[p_nbr] = (t_list*)ft_memalloc(sizeof(pieces) * 27);
	start = pieces[0];
	end = pieces[p_nbr];
	while ((rd = read(file, tet, BUF)) == BUF)
	{
		tet[BUF - 1] = 0;
		if (p_nbr >= 26 || (!(tet_lstadd(&start, &end, tet, p_nbr) == 1)))
			return (0);
		p_nbr++;
	}
	if (rd == BUF - 1)
	{
		if (p_nbr >= 26 || (!(tet_lstadd(&start, &end, tet, p_nbr) == 1)))
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
	t_list			*start;
	t_list			*end;

	if (ac == 2)
	{
		if (!(file = open(av[1], O_RDONLY)))
			return (0);
		start = NULL;
		end = NULL;
		if (!(pieces = read_file(&pieces, file, start, end)))
		{
			ft_putendl("error");
			close(file);
			return (0);
		}
		if (!map_solve(&pieces))
			return (0);
	}
	else
	{
		ft_putendl("\nusage: fillit [input_file]");
		return (0);
	}
	return (1);
}
