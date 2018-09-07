/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:26:04 by okovalov          #+#    #+#             */
/*   Updated: 2018/08/13 12:34:22 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		compare(t_lmn *lmn, int i)
{
	t_list	*begin;
	t_list	*bg;

	begin = lmn->way;
	while (begin)
	{
		if (lenfre((t_list *)begin->content, i))
		{
			bg = begin->next;
			while (bg)
			{
				if (!bg->next)
					return ;
				if (lenfre((t_list *)bg->content, i))
				{
					lenlist(begin->content) < lenlist(bg->content) ?
						dellist(((t_list **)&(bg->content))) :
						dellist(((t_list **)&(begin->content)));
					return ;
				}
				bg = begin->next;
			}
		}
		begin = begin->next;
	}
}

int			strtend(t_lmn *lmn, char *buf)
{
	char	c;
	char	*loc;

	if (!ft_strcmp(buf, "##start") || !ft_strcmp(buf, "##end"))
	{
		c = (!ft_strcmp(buf, "##start") ? 's' : 'e');
		get_next_line(0, &loc);
		ft_lstpushback(&lmn->all, loc, ft_strlen(loc) + 1);
		if (loc[0] == 'L' || loc[0] == '#' || analyze(loc) != 0
			|| !ft_strcmp(loc, "##start") || !ft_strcmp(loc, "##end")
			|| !roomfnd(loc, lmn, c))
		{
			free(loc);
			return (0);
		}
		free(loc);
	}
	else
	{
		if (buf[0] == 'L' || buf[0] == '#' || !roomfnd(buf, lmn, 'o'))
			return (0);
	}
	return (1);
}

int			linkorroom(t_lmn *lmn, int *n, char *buf)
{
	int		rez;

	if ((rez = analyze(buf)) == -1
		|| (rez == 1 && *n == -1) || (rez == 0 && *n == 1))
		return (0);
	else if (rez == 0)
	{
		*n = 0;
		if (!strtend(lmn, buf))
			return (0);
	}
	else if (rez == 1)
	{
		*n = 1;
		if (linkfnd(buf, lmn) < 2)
			return (0);
	}
	return (1);
}

int			numofants(t_lmn *lmn, char *buf, int *n)
{
	int		i;

	if (get_next_line(0, &buf))
	{
		i = -1;
		while (buf[++i])
			if (ft_isalpha(buf[i]))
			{
				free(buf);
				return (0);
			}
		if ((*n = ft_atoi(buf)) > 0)
			lmn->nmbr = *n;
		else
		{
			free(buf);
			return (0);
		}
	}
	free(buf);
	*n = -1;
	return (1);
}

int			valid(t_lmn *lmn)
{
	char	*buf;
	int		n;

	buf = NULL;
	if (!numofants(lmn, buf, &n))
		return (0);
	while (get_next_line(0, &buf))
	{
		ft_lstpushback(&lmn->all, buf, ft_strlen(buf) + 1);
		if (buf[0] == '#' && (ft_strcmp(buf, "##start")
			&& ft_strcmp(buf, "##end")))
		{
			free(buf);
			continue;
		}
		if (!linkorroom(lmn, &n, buf))
		{
			free(buf);
			return (0);
		}
		free(buf);
	}
	if (lmn->end == -1 || lmn->str == -1 || n != 1)
		return (0);
	return (1);
}
