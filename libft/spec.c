/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 13:19:19 by okovalov          #+#    #+#             */
/*   Updated: 2017/10/11 12:51:37 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		f_ten(intmax_t value, char *str, intmax_t base, int *i)
{
	char	*tmp;

	tmp = "0123456789ABCDEF";
	if (value <= -base || value >= base)
		f_ten(value / base, str, base, i);
	str[(*i)++] = tmp[A(value % base)];
}

char		*ft_itoaspec(intmax_t value)
{
	int		i;
	char	*str;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * 32)))
		return (0);
	if (value < 0)
		str[i++] = '-';
	f_ten(value, str, 10, &i);
	str[i] = '\0';
	return (str);
}

void		put_wstr(char **d)
{
	int		a;
	int		j;

	a = 0;
	while (d[a])
	{
		j = 0;
		while (d[a][j])
		{
			ft_putchar_pr(d[a][j]);
			j++;
		}
		a++;
	}
}

int			check_len_wchar(char **data)
{
	int		i;
	int		tmp;

	i = 0;
	tmp = 0;
	while (data[i])
	{
		tmp += ft_strlen(data[i]);
		i++;
	}
	return (tmp);
}

void		wldcr(t_prnt *prf, va_list ap)
{
	if (prf->shur[0] == -2)
	{
		prf->shur[0] = (va_arg(ap, int));
		if (prf->shur[0] < 0)
		{
			prf->shur[0] *= -1;
			prf->flg[0] = '-';
		}
	}
	if (prf->tochn[0] == -2)
		prf->tochn[0] = va_arg(ap, int);
	prf->tochn[1] = prf->tochn[0];
	prf->shur[1] = prf->shur[0];
}
