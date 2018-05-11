/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 20:02:13 by jfleisch          #+#    #+#             */
/*   Updated: 2018/04/14 20:02:15 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void 		ft_lstprint(t_list *list)
{
	while (list)
	{
		ft_putstr((char*)(list->cont));
		ft_putchar('\n');
		list = list->next;
	}
}
