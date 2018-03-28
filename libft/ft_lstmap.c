/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 11:20:16 by okovalov          #+#    #+#             */
/*   Updated: 2016/12/02 13:58:50 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *list;
	t_list *i;

	if (!lst)
		return (NULL);
	list = ft_lstnew(lst->content, lst->content_size);
	list = f(list);
	i = list;
	lst = lst->next;
	while (lst)
	{
		list->next = f(ft_lstnew(lst->content, lst->content_size));
		list = list->next;
		lst = lst->next;
	}
	list->next = NULL;
	return (i);
}
