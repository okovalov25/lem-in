/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 12:10:17 by okovalov          #+#    #+#             */
/*   Updated: 2018/08/09 13:08:46 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			findway(t_lmn *lmn, int i, t_list *begin)
{
	int		j;
	int		r;

	j = -1;
	if (lmn->mtrx[i][lmn->end] == 1)
	{
		ft_lstpushback((t_list **)&begin->content, &lmn->end, sizeof(int));
		return (1);
	}
	while (++j <= lmn->id)
	{
		if (lmn->mtrx[i][j] == 1)
		{
			if (lmn->mtrxv[j] == 1)
				continue;
			else if (lmn->mtrxv[j] == 0)
			{
				lmn->mtrxv[j] = 1;
				ft_lstpushback((t_list **)&begin->content, &j, sizeof(int));
				r = findway(lmn, j, begin);
				return (r);
			}
		}
	}
	return (0);
}

void		recurwork(t_lmn *lmn, t_list **begin, int i)
{
	t_list	*bg;

	bg = *begin;
	if (i == lmn->end && lmn->wid++ > -1)
	{
		ft_lstpushback((t_list **)&bg->content, &lmn->str, sizeof(int));
		ft_lstpushback((t_list **)&bg->content, &lmn->end, sizeof(int));
		bg->next = ft_lstnew(NULL, 0);
		bg = bg->next;
	}
	else
	{
		lmn->mtrxv[i] = 1;
		if (findway(lmn, i, bg) && lmn->wid++ > -1)
		{
			ft_lstadd((t_list **)&bg->content, ft_lstnew(&i, sizeof(int)));
			ft_lstadd((t_list **)&bg->content,
				ft_lstnew(&lmn->str, sizeof(int)));
			bg->next = ft_lstnew(NULL, 0);
			bg = bg->next;
		}
		else
			free(bg->content);
	}
	*begin = bg;
}

void		recur(t_lmn *lmn)
{
	t_list	*begin;
	int		i;
	int		j;

	i = -1;
	begin = ft_lstnew(NULL, 0);
	lmn->way = begin;
	while (++i <= lmn->id)
	{
		if (lmn->mtrx[lmn->str][i] == 1)
		{
			lmn->mtrxv[lmn->str] = 1;
			recurwork(lmn, &begin, i);
		}
		j = 0;
		while (j <= lmn->id)
		{
			lmn->vroom[j] += lmn->mtrxv[j];
			lmn->mtrxv[j] = 0;
			j++;
		}
	}
	begin->content = NULL;
	lmn->vroom[lmn->str] = 0;
}

void		filtrwork(t_lmn *lmn, t_list **g, t_list **begin)
{
	t_list	*n;
	t_list	*gg;

	gg = *g;
	if (!gg)
	{
		gg = lmn->way->next;
		lmn->way->next = NULL;
		lmn->way = gg;
		free(*begin);
		*begin = gg;
	}
	else
	{
		if (lmn->way->next)
		{
			n = lmn->way->next;
			lmn->way->next = NULL;
			gg->next = n;
		}
		else
			gg->next = NULL;
	}
	*g = gg;
}

void		filtr(t_lmn *lmn)
{
	int		i;
	t_list	*begin;
	t_list	*g;

	i = -1;
	while (++i <= lmn->id)
	{
		if (lmn->vroom[i] >= 2)
		{
			compare(lmn, i);
			lmn->vroom[i]--;
			i = -1;
		}
	}
	begin = lmn->way;
	g = NULL;
	while (lmn->way)
	{
		if (!lmn->way->content)
			filtrwork(lmn, &g, &begin);
		g = lmn->way;
		lmn->way = lmn->way->next;
	}
	lmn->way = begin;
	free(g);
}
