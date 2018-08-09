/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:20:18 by okovalov          #+#    #+#             */
/*   Updated: 2018/07/04 14:24:44 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rms		*roomnew(t_coor *cr, int id)
{
	t_rms	*list;

	list = (t_rms *)malloc(sizeof(t_rms));
	if (!list)
		return (NULL);
	if (!cr)
	{
		list->name = NULL;
		list->links = NULL;
	}
	else
	{
		list->name = (char *)malloc(sizeof(cr->name) * ft_strlen(cr->name) + 1);
		ft_strcpy(list->name, cr->name);
		list->x = cr->x;
		list->y = cr->y;
		list->links = NULL;
		list->id = id;
	}
	list->next = NULL;
	return (list);
}

void		lstroompush(t_rms **list, t_coor *cr, int id)
{
	t_rms	*node;

	node = *list;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = roomnew(cr, id);
	}
	else
		*list = roomnew(cr, id);
}

t_coor		namecoor(char *buf, t_coor cr)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (buf[i] != ' ')
		i++;
	cr.name = ft_strsub(buf, 0, i);
	j = i++;
	while (buf[i] != ' ')
		i++;
	s = ft_strsub(buf, j, i);
	cr.x = ft_atoi(s);
	free(s);
	j = i++;
	while (buf[i])
		i++;
	s = ft_strsub(buf, j, i - 1);
	cr.y = ft_atoi(s);
	free(s);
	return (cr);
}

int			links(t_lmn *lmn, int i, int j)
{
	t_rms	*tmp;
	t_list	*lnk;

	tmp = lmn->rms;
	while (tmp)
	{
		if (tmp->id == j)
		{
			lnk = tmp->links;
			while (lnk)
			{
				tmp = lmn->rms;
				while (tmp)
				{
					if (tmp->id == i && !ft_strcmp(lnk->content, tmp->name))
						return (1);
					tmp = tmp->next;
				}
				lnk = lnk->next;
			}
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int			lenfre(t_list *rm, int i)
{
	int		*id;

	while (rm)
	{
		id = rm->content;
		if (*id == i)
			return (1);
		rm = rm->next;
	}
	return (0);
}
