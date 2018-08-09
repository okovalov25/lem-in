/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 13:24:29 by okovalov          #+#    #+#             */
/*   Updated: 2018/08/09 13:54:20 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			analyze2(char *buf, int *spc, int *er, int *i)
{
	if (buf[*i] == ' ')
	{
		(*er)++;
		(*spc)++;
		(*i)++;
		if (buf[*i] == '-')
			(*i)++;
		if (!buf[*i] || (buf[*i] < '0' || buf[*i] > '9'))
			return (0);
	}
	return (1);
}

int			analyze(char *buf)
{
	int		i;
	int		spc;
	int		rez;
	int		er;

	i = -1;
	er = 0;
	spc = 0;
	rez = 0;
	if (!ft_strcmp(buf, "##start") || !ft_strcmp(buf, "##end"))
		return (0);
	while (buf[++i])
	{
		if (!analyze2(buf, &spc, &er, &i))
			return (-1);
		if (buf[i] == '-')
		{
			er++;
			rez = 1;
		}
	}
	if ((spc > 0 && spc < 2) || er == 0)
		return (-1);
	return (rez);
}

char		*idtoname(t_lmn *lmn, int i)
{
	t_rms	*begin;

	begin = lmn->rms;
	while (begin)
	{
		if (begin->id == i)
			return (begin->name);
		begin = begin->next;
	}
	return (NULL);
}

void		printout(t_lmn *lmn)
{
	t_list	*g;
	t_list	*bg;
	int		*id;

	bg = lmn->way;
	ft_printf("\n");
	while (bg)
	{
		g = (t_list *)bg->content;
		while (g)
		{
			id = g->content;
			ft_printf("%s ", idtoname(lmn, *id));
			g = g->next;
		}
		ft_printf("\n");
		bg = bg->next;
	}
}

void		printin(t_lmn *lmn)
{
	t_list	*tmp;

	tmp = lmn->all;
	printf("%d\n", lmn->nmbr);
	while (tmp)
	{
		printf("%s\n", (char*)tmp->content);
		tmp = tmp->next;
	}
	ft_printf("\n");
	ant(lmn);
}
