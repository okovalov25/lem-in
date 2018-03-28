/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 13:33:10 by okovalov          #+#    #+#             */
/*   Updated: 2018/01/15 17:58:03 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					specform2(const char *format, int i, t_prnt *prf)
{
	prf->jj = 0;
	while (prf->flg[prf->jj] && prf->jj < 5)
		prf->flg[prf->jj++] = 'n';
	prf->jj = 0;
	i = flag(format, i, prf);
	if (format[i] >= '0' && format[i] <= '9')
		i = num(format, i, &prf->shur[0], prf);
	if (format[i] == '*')
	{
		prf->shur[0] = -2;
		i++;
	}
	i = flag(format, i, prf);
	return (i);
}

int					specform3(const char *format, int i, t_prnt *prf)
{
	if (format[i] == '.')
	{
		i++;
		prf->tochn[0] = 0;
		if (format[i] == '*')
		{
			prf->tochn[0] = -2;
			i++;
		}
		i = num(format, i, &prf->tochn[0], prf);
	}
	i = hl(format, i, prf);
	if (format[i] == 'h' || format[i] == 'l'
		|| format[i] == 'j' || format[i] == 'z')
		prf->razm = format[i++];
	return (i);
}

int					num(const char *format, int i, int *st, t_prnt *prf)
{
	unsigned int	j;

	j = 0;
	while (format[i] >= '0' && format[i] <= '9')
	{
		i++;
		j++;
	}
	if (j > 0)
	{
		prf->buf = ft_strsub(format, i - j, j);
		*st = ft_atoi(prf->buf);
		free(prf->buf);
	}
	i = flag(format, i, prf);
	return (i);
}

t_prnt				specform(const char *format, int i)
{
	t_prnt			prf;

	prf.tup = 'a';
	prf.tochn[0] = -1;
	prf.shur[0] = -1;
	prf.razm = 'n';
	i = specform2(format, i, &prf);
	i = flag(format, i, &prf);
	i = specform3(format, i, &prf);
	if (format[i] == 's' || format[i] == 'S' || format[i] == 'p'
		|| format[i] == 'd' || format[i] == 'i' || format[i] == 'o'
		|| format[i] == 'O' || format[i] == 'u' || format[i] == 'U'
		|| format[i] == 'x' || format[i] == 'X' || format[i] == 'c'
		|| format[i] == 'C' || format[i] == 'D' || format[i] == '%')
		prf.tup = format[i];
	if (prf.tup == 'a')
		prf.tup = 'n';
	prf.i = i;
	return (prf);
}

int					ft_printf(const char *format, ...)
{
	int				i;
	va_list			ap;

	i = 0;
	g_ns = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && (!format[i + 1] || (!format[i + 2]
			&& format[i + 1] == ' ')))
			break ;
		i = color(format, i);
		while (format[i] == '%' && format[i + 1] == '%')
		{
			ft_putchar_pr('%');
			i += 2;
		}
		i = percent(format, i, ap);
	}
	va_end(ap);
	return (g_ns);
}
