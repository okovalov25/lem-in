/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:26:04 by okovalov          #+#    #+#             */
/*   Updated: 2018/08/02 13:24:05 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		roomfndsne(t_lmn *lmn, char c, t_coor cr)
{
	t_rms	*tmp;

	tmp = lmn->rms;
	while (tmp->next)
	{
		if (tmp->name == cr.name)
			ft_lstpushback(&tmp->links, (c == 's' ? "start" : "end!!"), 6);
		tmp = tmp->next;
	}
	if (c == 's' && lmn->str == -1)
		lmn->str = lmn->id;
	else if (c == 'e' && lmn->end == -1)
		lmn->end = lmn->id;
}

int			roomfnd(char *buf, t_lmn *lmn, char c)
{
	t_coor	cr;
	t_rms	*rm;

	rm = lmn->rms;
	cr.name = NULL;
	lmn->id++;
	cr = namecoor(buf, cr);
	while (rm)
	{
		if (!ft_strcmp(rm->name, cr.name) || (rm->x == cr.x && rm->y == cr.y))
		{
			free(cr.name);
			return (0);
		}
		rm = rm->next;
	}
	lstroompush(&lmn->rms, &cr, lmn->id);
	if (c == 's' || c == 'e')
		roomfndsne(lmn, c, cr);
	free(cr.name);
	return (1);
}

int			linkfnd3(char *t, char *l, t_list *link)
{
	if (!ft_strcmp((char *)link->content, l))
	{
		free(t);
		free(l);
		return (0);
	}
	return (1);
}

int			linkfnd2(t_lmn *lmn, char *l, char *t, int *i)
{
	t_rms	*tmp;
	t_list	*link;

	tmp = lmn->rms;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, t))
		{
			if (tmp->links)
				if (tmp->links->content)
				{
					link = tmp->links;
					while (link->next)
					{
						if (!linkfnd3(t, l, link))
							return (0);
						link = link->next;
					}
				}
			ft_lstpushback(&tmp->links, l, ft_strlen(l) + 1);
			(*i)++;
		}
		tmp = tmp->next;
	}
	return (1);
}

int			linkfnd(char *buf, t_lmn *lmn)
{
	int		i;
	char	*t;
	char	*l;
	t_rms	*tmp;

	i = 0;
	while (buf[i] != '-')
		i++;
	t = ft_strsub(buf, 0, i);
	l = ft_strsub(buf, i + 1, ft_strlen(buf));
	i = 0;
	if (!linkfnd2(lmn, l, t, &i))
		return (0);
	tmp = lmn->rms;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, l) && i++)
			ft_lstpushback(&tmp->links, t, ft_strlen(t) + 1);
		tmp = tmp->next;
	}
	free(t);
	free(l);
	return (i);
}
