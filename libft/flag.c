/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:58:35 by okovalov          #+#    #+#             */
/*   Updated: 2018/01/15 18:03:32 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		flag(const char *format, int i, t_prnt *prf)
{
	while (format[i] == '-' || format[i] == '+'
		|| format[i] == ' ' || format[i] == '#' || format[i] == '0')
	{
		if (prf->flg[prf->jj] && prf->jj < 5)
			prf->jj++;
		prf->flg[prf->jj] = format[i++];
	}
	return (i);
}

int		hl(const char *format, int i, t_prnt *prf)
{
	if (format[i] == 'h' && (format[i + 1] == 'h'
		|| (format[i + 1] == ' ' && format[i + 2] == 'h')))
	{
		if (format[i + 1] == ' ' && prf->jj < 5)
		{
			prf->flg[prf->jj] = ' ';
			i++;
		}
		i += 2;
		prf->razm = 'H';
	}
	if (format[i] == 'l' && (format[i + 1] == 'l'
		|| (format[i + 1] == ' ' && format[i + 2] == 'l')))
	{
		if (format[i + 1] == ' ' && prf->jj < 5)
		{
			prf->flg[prf->jj] = ' ';
			i++;
		}
		i += 2;
		prf->razm = 'L';
	}
	return (i);
}

void	minuso(t_prnt prf)
{
	if (ft_strchr(prf.flg, '-'))
	{
		if (prf.tochn[1] < prf.lng && ft_strchr(prf.flg, '#'))
			prf.shur[0]--;
		while (prf.shur[0]--
			- (prf.tochn[1] > prf.lng ? prf.tochn[1] : prf.lng) >= 1)
			ft_putchar_pr(' ');
	}
}

void	minusx(t_prnt prf)
{
	if (ft_strchr(prf.flg, '-'))
		while (prf.shur[0]-- - (prf.tochn[1] > prf.lng ? prf.tochn[1] : prf.lng)
			- (ft_strchr(prf.flg, '#') ? 2 : 0) >= 1)
			ft_putchar_pr(' ');
}

void	normd(t_prnt *prf, va_list ap, intmax_t *tem)
{
	if (prf->razm == 'l' || prf->tup == 'D')
		*tem = (va_arg(ap, long));
	else if (prf->razm == 'h')
		*tem = (short)(va_arg(ap, int));
	else if (prf->razm == 'L')
		*tem = (va_arg(ap, long long));
	else if (prf->razm == 'j')
		*tem = (va_arg(ap, intmax_t));
	else if (prf->razm == 'z')
		*tem = (va_arg(ap, size_t));
	else if (prf->razm == 'H')
		*tem = (char)(va_arg(ap, int));
	else
		*tem = va_arg(ap, int);
}
