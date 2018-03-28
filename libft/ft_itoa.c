/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 12:42:44 by okovalov          #+#    #+#             */
/*   Updated: 2016/12/14 10:42:58 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_prnt(int n, char *s, int flag, int i)
{
	s[i] = '\0';
	if (n == 0)
		s[0] = 48;
	if (flag == 1)
	{
		flag = 0;
		s[0] = '-';
		s[--i] = (char)((n % 10) + 48 + 1);
		n /= 10;
	}
	while (n > 0)
	{
		s[--i] = (char)((n % 10) + 48);
		n /= 10;
	}
	return (s);
}

char			*ft_itoa(int n)
{
	int			i;
	int			flag;
	char		*s;
	int			j;

	i = 0;
	flag = 0;
	if (n < 0)
	{
		flag = 1;
		n = (-n) - 1;
		i++;
	}
	j = n;
	if (n == 0)
		i++;
	while (j > 0)
	{
		i++;
		j /= 10;
	}
	if (!(s = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	return (ft_prnt(n, s, flag, i));
}
