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

void 			free_tetris(t_etris **tetris)
{
	int			height;

	if (!tetris)
		return ;
	free_point(&((*tetris)->first));
	if ((*tetris)->shape)
	{
		height = 0;
		while (height < (*tetris)->height)
			ft_strdel(&((*tetris)->shape[height++]));
		free((*tetris)->shape);
	}
	free (*tetris);
	*tetris = NULL;
}

t_list			*tet_lstnew(char *tet, int id)
{
	t_etris		*tetris;
	t_list		*node;

	if (!(tetris = make_piece(tet, id)))
		return (NULL);
	if (!(node = ft_lstnew((void*)tetris, sizeof(tetris))))
	{
		free_tetris(&tetris);
		return (NULL);
	}
	return (node);
}

static void 		lstdel_tetris(void *cont, size_t cont_size)
{
	(void)cont_size;
	free_tetris((t_etris**)&cont);
}

int			tet_lstadd(t_list **start, t_list **end, char *tet, int p_nbr)
{
	if (p_nbr && ((*end)->next = tet_lstnew(tet, 'A' + p_nbr)))
		*end = (*end)->next;
	else if ((*start = tet_lstnew(tet, 'A' + p_nbr)))
		*end = *start;
	else
	{
		ft_lstdel(start, &lstdel_tetris);
		return (0);
	}
	return (1);
}
