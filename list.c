/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 13:33:51 by okovalov          #+#    #+#             */
/*   Updated: 2018/08/09 14:43:53 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			lenlist(t_list *list)
{
	int		i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void		dellist(t_list **list)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *list;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
		tmp = next;
	}
	*list = NULL;
}

int			antcheck(int *ants, int n, int end)
{
	int		i;

	i = -1;
	while (++i < n)
		if (ants[i] != end)
			return (0);
	return (1);
}

void		ant(t_lmn *lmn)
{
	int		*ants;
	int		i;
	int		r;

	i = -1;
	ants = (int *)malloc(sizeof(int) * lmn->nmbr);
	while (++i < lmn->nmbr)
		ants[i] = lmn->str;
	while (!antcheck(ants, lmn->nmbr, lmn->end))
	{
		lmn->entr = -1;
		i = -1;
		while (++i < lmn->nmbr)
		{
			if (ants[i] == lmn->end)
				continue;
			r = moveant(ants[i], lmn);
			if (r > -1 && (ants[i] = r) > -2)
				printf("L%d-%s ", i + 1, idtoname(lmn, ants[i]));
		}
		printf("\n");
	}
	free(ants);
}

void		matrix(t_lmn *lmn)
{
	int		j;
	int		i;

	j = -1;
	lmn->mtrx = (int **)malloc(sizeof(int *) * lmn->id + 1);
	lmn->mtrxv = (int *)malloc(sizeof(int) * lmn->id + 1);
	lmn->vroom = (int *)malloc(sizeof(int) * lmn->id + 1);
	while (++j <= lmn->id)
	{
		i = -1;
		lmn->mtrx[j] = (int *)malloc(sizeof(int) * lmn->id + 1);
		while (++i <= lmn->id)
		{
			lmn->mtrxv[i] = 0;
			lmn->vroom[i] = 0;
			lmn->mtrxv[lmn->str] = 1;
			if (i == j)
				lmn->mtrx[j][i] = 0;
			else if (links(lmn, j, i))
				lmn->mtrx[j][i] = 1;
			else
				lmn->mtrx[j][i] = 0;
		}
	}
}
