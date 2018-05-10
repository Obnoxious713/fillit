/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <jfleisch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:44:36 by jfleisch          #+#    #+#             */
/*   Updated: 2018/05/06 15:45:43 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"
#include <stdio.h>

/*
**	tet_lstnew() takes tet and calls makes_piece() whose return is stored into
**	the t_etris which is then stored into node by calling ft_lstnew()
*/
t_list			*tet_lstnew(char *tet, int id)
{
	t_etris		*tetris;
	t_list		*node;

	if (!(tetris = make_piece(tet, id)))
	{
		ft_putendl("\ntet_lstnew !tetris");
		return (NULL);
	}
	if (!(node = ft_lstnew((void*)tetris, sizeof(tetris))))
	{
		ft_putendl("\ntet_lstnew !node");
		//free_tetris(&tetris);
		return (NULL);
	}
	return (node);
}

/*
**	tet_lstadd() checks that there is a piece and stores the return
**	from tet_lstnew() into the next element then moves to the next empty postion
**	and deletes the element otherwise
*/
int			tet_lstadd(t_list **start, t_list **end, char *tet, int p_nbr)
{
	if (p_nbr && ((*end)->next = tet_lstnew(tet, 'A' + p_nbr)))
		*end = (*end)->next;
	else if ((*start = tet_lstnew(tet, 'A' + p_nbr)))
		*end = *start;
	else
	{
		ft_putendl("\ntet_lstadd 'else' ft_lstdel called");
		//ft_lstdel(start, &lstdel_tetris);
		return (0);
	}
	return (1);
}
