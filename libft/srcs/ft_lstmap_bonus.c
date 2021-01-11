/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:26:28 by tfevrier          #+#    #+#             */
/*   Updated: 2019/10/11 18:00:50 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *))
{
	t_list	*new_list;

	new_list = NULL;
	while (lst)
	{
		ft_lstadd_back(&new_list, ft_lstnew((*f)(lst->content)));
		lst = lst->next;
	}
	return (new_list);
}
