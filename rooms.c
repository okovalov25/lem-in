/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:20:18 by okovalov          #+#    #+#             */
/*   Updated: 2018/02/20 15:20:37 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_rms	*roomnew(char *content, int id)
{
    t_rms	*list;

    list = (t_rms *)malloc(sizeof(t_rms));
    if (!list)
        return (NULL);
    if (!content)
    {
        list->name = NULL;
        list->links = NULL;
    }
    else
    {
        list->name = (char *)malloc(sizeof(content) * ft_strlen(content) + 1);
        ft_strcpy(list->name, content);
        list->links = NULL;
        list->id = id;
    }
    list->next = NULL;
    return (list);
}


void			lstroompush(t_rms **list, char *content, int id)
{
    t_rms		*node;

    node = *list;
    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = roomnew(content, id);
    }
    else
        *list = roomnew(content, id);
}