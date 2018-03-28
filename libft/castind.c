/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castind.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:41:27 by okovalov          #+#    #+#             */
/*   Updated: 2018/01/15 17:51:01 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			cind2(t_prnt *prf, va_list ap, intmax_t *tem)
{
	normd(prf, ap, tem);
	prf->buf = ft_itoaspec(*tem);
	prf->temp = prf->buf;
	free(prf->buf);
	prf->lng = (int)(ft_strlen(prf->temp));
	if (prf->temp[0] == '-' || ft_strchr(prf->flg, '+'))
		prf->shur[0]--;
	if (ft_strchr(prf->flg, ' ') && !ft_strchr(prf->flg, '+')
		&& prf->temp[0] != '-')
	{
		ft_putchar_pr(' ');
		prf->shur[0]--;
	}
	if (prf->temp[0] == '-' && ft_strchr(prf->flg, '0') && prf->tochn[1] >= 0)
		prf->lng--;
}

void			cind3(t_prnt prf, intmax_t tem)
{
	if (prf.temp[0] == '-' && (!ft_strchr(prf.flg, '0') || prf.tochn[1] >= 0))
	{
		ft_putchar_pr('-');
		prf.buf = prf.temp;
		prf.temp = ft_strsub(prf.buf, 1, ft_strlen(prf.temp) - 1);
		free(prf.buf);
		prf.lng = (int)(ft_strlen(prf.temp));
	}
	else if (ft_strchr(prf.flg, '+') && !ft_strchr(prf.flg, '0'))
		ft_putchar_pr('+');
	if (prf.tochn[1] > 0)
		while (prf.tochn[0]-- > prf.lng)
		{
			ft_putchar_pr('0');
			prf.shur[0]--;
		}
	if (prf.tochn[1] == 0 && tem == 0 && prf.shur[1] > 0)
		ft_putchar_pr(' ');
	else if (prf.tochn[1] == 0 && tem == 0 && prf.shur[1] < 0)
		prf.tochn[0]++;
	else
		ft_putstr_pr(prf.temp);
	if (ft_strchr(prf.flg, '-'))
		while (prf.shur[0]-- - prf.lng >= 1)
			ft_putchar_pr(' ');
}

void			cind(t_prnt prf, va_list ap)
{
	intmax_t	tem;

	cind2(&prf, ap, &tem);
	if (prf.temp[0] == '-' && ft_strchr(prf.flg, '0') && prf.tochn[1] <= 0)
	{
		ft_putchar_pr('-');
		prf.buf = prf.temp;
		prf.temp = ft_strsub(prf.buf, 1, ft_strlen(prf.temp) - 1);
		free(prf.buf);
		prf.lng = (int)(ft_strlen(prf.temp));
	}
	else if (ft_strchr(prf.flg, '+') && ft_strchr(prf.flg, '0'))
		ft_putchar_pr('+');
	if (!ft_strchr(prf.flg, '-'))
	{
		while (prf.shur[0]--
			- (prf.tochn[0] > prf.lng ? prf.tochn[0] : prf.lng)
			+ (prf.tochn[1] == -1 && prf.temp[0] == '-'
			&& !ft_strchr(prf.flg, '0') ? 1 : 0)
			+ (prf.tochn[0] < prf.lng && prf.tochn[1] > 0
			&& prf.temp[0] == '-' && !ft_strchr(prf.flg, '0') ? 1 : 0) >= 1)
			zero(prf, 0);
	}
	cind3(prf, tem);
}

int				color(const char *format, int i)
{
	if (format[i] == '{' && (format[i + 1] == 'r' || format[i + 1] == 'g'
				|| format[i + 1] == 'b' || format[i + 1] == 'y'
				|| format[i + 1] == 'm' || format[i + 1] == 'c'
				|| format[i + 1] == 'R') && format[i + 2] == '}')
	{
		i++;
		if (format[i] == 'r')
			ft_putstr_pr("\x1b[31m");
		else if (format[i] == 'g')
			ft_putstr_pr("\x1b[32m");
		else if (format[i] == 'y')
			ft_putstr_pr("\x1b[33m");
		else if (format[i] == 'b')
			ft_putstr_pr("\x1b[34m");
		else if (format[i] == 'm')
			ft_putstr_pr("\x1b[35m");
		else if (format[i] == 'c')
			ft_putstr_pr("\x1b[36m");
		else if (format[i] == 'R')
			ft_putstr_pr("\x1b[0m");
		i += 2;
	}
	return (i);
}

int				percent(const char *format, int i, va_list ap)
{
	int			j;

	if (format[i] == '%' && format[i + 1] && format[i + 1] != '%')
	{
		j = cast(specform(format, i + 1), ap);
		i = j;
		i++;
	}
	else if (format[i])
		ft_putchar_pr(format[i++]);
	return (i);
}
