/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 15:02:51 by okovalov          #+#    #+#             */
/*   Updated: 2017/10/23 17:34:03 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t		casttype(uintmax_t *tem, t_prnt prf, va_list ap)
{
	if (prf.razm == 'l' || prf.tup == 'U' || prf.tup == 'O')
		*tem = (va_arg(ap, unsigned long));
	else if (prf.razm == 'h')
		*tem = (unsigned short)(va_arg(ap, unsigned int));
	else if (prf.razm == 'L')
		*tem = (va_arg(ap, unsigned long long));
	else if (prf.razm == 'j')
		*tem = (va_arg(ap, uintmax_t));
	else if (prf.razm == 'z')
		*tem = (va_arg(ap, size_t));
	else if (prf.razm == 'H')
		*tem = (unsigned char)(va_arg(ap, unsigned int));
	else
		*tem = va_arg(ap, unsigned int);
	return (*tem);
}

void			cinu(t_prnt prf, va_list ap)
{
	uintmax_t	tem;

	tem = 0;
	casttype(&tem, prf, ap);
	prf.temp = ft_itoa_base(tem, 10, 0);
	prf.lng = (int)(ft_strlen(prf.temp));
	if (!ft_strchr(prf.flg, '-'))
		while (prf.shur[0]--
			- (prf.tochn[1] > prf.lng ? prf.tochn[1] : prf.lng) >= 1)
			zero(prf, 2);
	if (prf.tochn[1] > 0)
		while (prf.tochn[0]-- > prf.lng)
			ft_putchar_pr('0');
	if (prf.tochn[1] != 0)
		ft_putstr_pr(prf.temp);
	else if (prf.shur[1] > 0)
		ft_putchar_pr(' ');
	if (ft_strchr(prf.flg, '-'))
		while ((prf.shur[0]--
			- (prf.tochn[1] > prf.lng ? prf.tochn[1] : prf.lng)) >= 1)
			ft_putchar_pr(' ');
}

void			cinx(t_prnt prf, va_list ap)
{
	uintmax_t	tem;

	casttype(&tem, prf, ap);
	prf.temp = ft_itoa_base(tem, 16, (prf.tup == 'x' ? 0 : 1));
	prf.lng = (int)(ft_strlen(prf.temp));
	if (ft_strchr(prf.flg, '#') && tem != 0 && (ft_strchr(prf.flg, '0')
		&& prf.tochn[1] < 0))
		ft_putstr_pr((prf.tup == 'x' ? "0x" : "0X"));
	if (!ft_strchr(prf.flg, '-'))
		while (prf.shur[0]-- - (prf.tochn[1] > prf.lng ? prf.tochn[1] : prf.lng)
			- (ft_strchr(prf.flg, '#') ? 2 : 0) >= 1)
			zero(prf, 2);
	if (ft_strchr(prf.flg, '#') && tem != 0 && (!ft_strchr(prf.flg, '0')
		|| prf.tochn[1] > 0))
		ft_putstr_pr((prf.tup == 'x' ? "0x" : "0X"));
	if (prf.tochn[1] > 0)
		while (prf.tochn[0]-- > prf.lng)
			ft_putchar_pr('0');
	if (prf.tochn[1] != 0)
		ft_putstr_pr(prf.temp);
	else if (prf.shur[1] > 0)
		ft_putchar_pr(' ');
	minusx(prf);
}

void			cino(t_prnt prf, va_list ap)
{
	uintmax_t	tem;

	casttype(&tem, prf, ap);
	prf.temp = ft_itoa_base(tem, 8, 0);
	prf.lng = (int)(ft_strlen(prf.temp));
	if (prf.tochn[1] > prf.lng && ft_strchr(prf.flg, '#')
		&& ft_strchr(prf.flg, '0'))
		prf.shur[0]++;
	if (!ft_strchr(prf.flg, '-'))
		while (prf.shur[0]-- - (prf.tochn[1] > prf.lng ? prf.tochn[1] : prf.lng)
			- (ft_strchr(prf.flg, '#') ? 1 : 0) >= 1)
			zero(prf, 2);
	if (ft_strchr(prf.flg, '#'))
		ft_putstr_pr("0");
	if (prf.tochn[1] > 0)
		while (prf.tochn[0]-- - (ft_strchr(prf.flg, '#') ? 1 : 0) > prf.lng)
			ft_putchar_pr('0');
	if (prf.temp[0] == '0' && ft_strchr(prf.flg, '#') && prf.tochn[1] <= 0)
		prf.tochn[0]++;
	else if (prf.tochn[1] != 0)
		ft_putstr_pr(prf.temp);
	else if (prf.shur[1] > 0)
		ft_putchar_pr(' ');
	minuso(prf);
}

void			zero(t_prnt prf, int f)
{
	if (f == 1)
	{
		if (ft_strchr(prf.flg, '0'))
			ft_putchar_pr('0');
		else
			ft_putchar_pr(' ');
	}
	else if (f == 0)
	{
		if (!ft_strchr(prf.flg, '0') || prf.tochn[1] >= 0)
			ft_putchar_pr(' ');
		else
			ft_putchar_pr('0');
	}
	else if (f == 2)
	{
		if (ft_strchr(prf.flg, '0') && prf.tochn[1] < 0)
			ft_putchar_pr('0');
		else
			ft_putchar_pr(' ');
	}
}
