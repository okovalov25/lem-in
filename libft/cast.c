/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 12:22:43 by okovalov          #+#    #+#             */
/*   Updated: 2018/01/15 17:29:50 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		cins(t_prnt prf, va_list ap)
{
	if ((prf.tup == 's' && prf.razm == 'l') || prf.tup == 'S')
		widestr(va_arg(ap, wchar_t*), prf);
	else if (prf.tup == 's' && prf.razm != 'l')
	{
		prf.temp = va_arg(ap, char*);
		if (prf.temp == NULL)
			prf.temp = "(null)";
		if (prf.tochn[1] >= 0)
		{
			prf.buf = prf.temp;
			prf.temp = ft_strsub(prf.buf, 0, (size_t)prf.tochn[1]);
			free(prf.buf);
		}
		prf.lng = (int)(ft_strlen(prf.temp));
		if (!ft_strchr(prf.flg, '-') && prf.shur[1] > prf.lng)
			while (prf.shur[0]-- - prf.lng >= 1)
				zero(prf, 1);
		ft_putstr_pr(prf.temp);
		if (ft_strchr(prf.flg, '-') && prf.shur[1] > prf.lng)
			while (prf.shur[0]-- - prf.lng >= 1)
				ft_putchar_pr(' ');
	}
}

void		cinp(t_prnt prf, va_list ap)
{
	prf.temp = ft_itoa_base((uintmax_t)va_arg(ap, void*), 16, 0);
	prf.lng = (int)(ft_strlen(prf.temp));
	if (prf.lng == 1 && prf.tochn[0] >= 0)
		prf.lng = 0;
	if (!ft_strchr(prf.flg, '-'))
		while (prf.shur[0]--
			- (prf.tochn[1] > prf.lng ? prf.tochn[1] : prf.lng) - 2 >= 1)
			zero(prf, 1);
	ft_putstr_pr("0x");
	if (prf.tochn[1] > 0)
		while (prf.tochn[0]-- > prf.lng)
		{
			ft_putchar_pr('0');
			prf.shur[0]--;
		}
	if (prf.lng > 1 || (prf.tochn[1] != 2 && prf.lng == 1))
		ft_putstr_pr(prf.temp);
	if (ft_strchr(prf.flg, '-'))
		while (prf.shur[0]--
			- (prf.tochn[1] > prf.lng ? prf.tochn[1] : prf.lng) - 2 >= 1)
			ft_putchar_pr(' ');
}

void		cinn(t_prnt prf)
{
	if (!ft_strchr(prf.flg, '-') && prf.shur[0] > 1)
	{
		while (prf.shur[0]-- - 1 >= 1)
			ft_putchar_pr(' ');
	}
	if (prf.tup == '%')
		ft_putchar_pr('%');
	if (ft_strchr(prf.flg, '-') && prf.shur[0] > 1)
	{
		while (prf.shur[0]-- - 1 >= 1)
			ft_putchar_pr(' ');
	}
}

void		cinc(t_prnt prf, va_list ap)
{
	if (!ft_strchr(prf.flg, '-'))
		while (prf.shur[0]-- > 1)
			zero(prf, 1);
	ft_putchar_pr((char)va_arg(ap, int));
	if (ft_strchr(prf.flg, '-'))
		while (prf.shur[0]-- > 1)
			ft_putchar_pr(' ');
}

int			cast(t_prnt prf, va_list ap)
{
	wldcr(&prf, ap);
	if (prf.tup == 'c' || prf.tup == 'C')
		cinc(prf, ap);
	if (prf.tup == 's' || prf.tup == 'S')
		cins(prf, ap);
	if (prf.tup == 'd' || prf.tup == 'i' || prf.tup == 'D')
		cind(prf, ap);
	if (prf.tup == 'x' || prf.tup == 'X')
		cinx(prf, ap);
	if (prf.tup == 'o' || prf.tup == 'O')
		cino(prf, ap);
	if (prf.tup == 'u' || prf.tup == 'U')
		cinu(prf, ap);
	if (prf.tup == 'p')
		cinp(prf, ap);
	if (prf.tup == 'n' || prf.tup == '%')
		cinn(prf);
	return (prf.i);
}
