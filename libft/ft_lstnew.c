/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:10:03 by jfleisch          #+#    #+#             */
/*   Updated: 2018/03/12 18:10:05 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list				*ft_lstnew(void const *cont, size_t cont_size)
{
	t_list *new;

	new = (t_list*)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	if (!cont)
	{
		new->cont = NULL;
		new->cont_size = 0;
		return (new);
	}
	new->cont = malloc(cont_size);
	ft_memcpy(new->cont, cont, cont_size);
	new->cont_size = cont_size;
	return (new);
}
