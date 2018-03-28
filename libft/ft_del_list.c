/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 12:43:30 by okovalov          #+#    #+#             */
/*   Updated: 2018/01/15 12:44:40 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_del_list(t_list **list)
{
	t_list		*node;
	t_list		*next;

	node = *list;
	while (node)
	{
		next = node->next;
		if (node->content)
			ft_memdel(&node->content);
		ft_memdel((void**)&node);
		node = next;
	}
	*list = NULL;
}
