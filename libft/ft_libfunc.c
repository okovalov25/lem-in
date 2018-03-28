/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:40:41 by okovalov          #+#    #+#             */
/*   Updated: 2017/10/06 13:22:30 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_pr(char const *s)
{
	if (s)
		while (*s)
		{
			write(1, &(*s), 1);
			g_ns++;
			s++;
		}
}

void	ft_putchar_pr(char c)
{
	write(1, &c, 1);
	g_ns++;
}
