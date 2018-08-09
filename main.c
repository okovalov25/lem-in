/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 14:06:43 by okovalov          #+#    #+#             */
/*   Updated: 2018/08/09 14:08:27 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			moveant2(t_lmn *lmn, t_list *begin, int a, int e)
{
	t_list	*g;
	int		c;

	g = (t_list *)begin->content;
	while (g)
	{
		if (g->content)
		{
			c = *((int *)g->content);
			if (c == a)
			{
				g = g->next;
				c = *((int *)g->content);
				if (a == lmn->str)
				{
					if (lmn->entr == e)
						return (c);
				}
				else
					return (c);
			}
		}
		g = g->next;
	}
	return (-1);
}

int			moveant(int a, t_lmn *lmn)
{
	t_list	*begin;
	int		e;
	int		c;

	e = 0;
	if (a == lmn->str)
		lmn->entr++;
	begin = lmn->way;
	while (begin)
	{
		if (begin->content)
		{
			if ((c = (moveant2(lmn, begin, a, e))) != -1)
				return (c);
		}
		begin = begin->next;
		e++;
	}
	return (-1);
}

void		initt(t_lmn *lmn)
{
	lmn->all = NULL;
	lmn->rms = NULL;
	lmn->way = NULL;
	lmn->id = -1;
	lmn->wid = 0;
	lmn->str = -1;
	lmn->end = -1;
}

int			main(int argc, char **argv)
{
	t_lmn	lmn;

	initt(&lmn);
	if (argc > 1 && ft_strcmp(argv[1], "-way"))
	{
		ft_printf("Usage : ./lem-in -way\n");
		return (0);
	}
	if (!valid(&lmn))
	{
		ft_printf("ERROR\n");
		return (0);
	}
	matrix(&lmn);
	recur(&lmn);
	if (!lmn.way->content)
	{
		ft_printf("ERROR\n");
		return (0);
	}
	filtr(&lmn);
	printin(&lmn);
	if (argc == 2 && !ft_strcmp(argv[1], "-way"))
		printout(&lmn);
	return (1);
}
