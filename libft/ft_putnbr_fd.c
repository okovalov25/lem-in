/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:17:20 by okovalov          #+#    #+#             */
/*   Updated: 2016/12/02 13:36:53 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putnbr_fd(int n, int fd)
{
	unsigned int	i;
	char			c;

	if (n < 0)
	{
		write(fd, "-", 1);
		i = -n;
	}
	else
		i = n;
	if (i <= 9)
	{
		c = i + '0';
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd(i / 10, fd);
		ft_putnbr_fd(i % 10, fd);
	}
}
