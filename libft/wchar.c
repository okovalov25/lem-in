/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 12:48:06 by okovalov          #+#    #+#             */
/*   Updated: 2017/10/23 15:09:54 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			place_wchar(int size, char c)
{
	int		i;

	i = 0;
	while (i < size)
	{
		ft_putchar_pr(c);
		i++;
	}
}

int				take_wlen(const uint32_t symbol)
{
	int			size;

	size = 0;
	if (symbol <= BIT7)
		size += 1;
	else if (symbol <= BIT11)
		size += 2;
	else if (symbol <= BIT16)
		size += 3;
	else if (symbol <= BIT21)
		size += 4;
	return (size);
}

char			*parse_wchar(const uint32_t symbol, int p)
{
	char		*rt;

	rt = ft_strnew(4);
	if (symbol <= BIT7 && p >= 1)
		rt[0] = symbol;
	else if (symbol <= BIT11 && p >= 2)
	{
		rt[0] = ((symbol & 1984) >> 6) | 192;
		rt[1] = (symbol & 63) | 128;
	}
	else if (symbol <= BIT16 && p >= 3)
	{
		rt[0] = ((symbol & 61440) >> 12) | 224;
		rt[1] = ((symbol & 4032) >> 6) | 128;
		rt[2] = (symbol & 63) | 128;
	}
	else if (symbol <= BIT21 && p >= 4)
	{
		rt[0] = ((symbol & 1835008) >> 18) | 240;
		rt[1] = ((symbol & 258048) >> 12) | 128;
		rt[2] = ((symbol & 4032) >> 6) | 128;
		rt[3] = (symbol & 63) | 128;
	}
	return (rt);
}

void			make_width(char **data, t_prnt prf)
{
	int i;

	i = 0;
	if (ft_strchr(prf.flg, '-'))
	{
		put_wstr(data);
		place_wchar(prf.shur[1] - check_len_wchar(data), ' ');
	}
	else if (ft_strchr(prf.flg, '0'))
	{
		place_wchar(prf.shur[1] - check_len_wchar(data), '0');
		put_wstr(data);
	}
	else
	{
		place_wchar(prf.shur[1] - check_len_wchar(data), ' ');
		put_wstr(data);
	}
	while (data[i])
		free(data[i++]);
	free(data);
}

void			widestr(wchar_t *d, t_prnt prf)
{
	int			i;
	int			p;
	char		**s;

	i = 0;
	if (d == NULL)
		d = L"(null)";
	while (d[i])
		i++;
	s = (char**)malloc(sizeof(char*) * (i + 1));
	s[i] = NULL;
	i = 0;
	p = prf.tochn[1];
	while (d[i])
	{
		if (prf.tochn[1] < 0)
			p = 4;
		s[i] = parse_wchar(d[i], p);
		p -= take_wlen(d[i]);
		i++;
	}
	make_width(s, prf);
}
