/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleisch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:09:30 by jfleisch          #+#    #+#             */
/*   Updated: 2018/03/12 18:09:31 by jfleisch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstdelone(t_list **alst, void ((*del)(void *, size_t)))
{
	if (!alst || !*alst)
		return ;
	if (del != NULL)
		del((*alst)->cont, (*alst)->cont_size);
	free(*alst);
	*alst = NULL;
}
