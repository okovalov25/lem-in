/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:11:44 by okovalov          #+#    #+#             */
/*   Updated: 2018/02/08 13:11:45 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstpushback(t_list **list, void *content, size_t size)
{
    t_list		*node;

    node = *list;
    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = ft_lstnew(content, size + 1);
    }
    else
        *list = ft_lstnew(content, size + 1);
}
