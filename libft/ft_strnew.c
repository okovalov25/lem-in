/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 14:47:13 by okovalov          #+#    #+#             */
/*   Updated: 2016/12/06 17:03:37 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*d;
	int		i;

	i = 0;
	d = (char *)malloc(sizeof(char) * size + 1);
	if (d)
	{
		while (size)
		{
			d[i++] = '\0';
			size--;
		}
		d[i] = '\0';
		return (d);
	}
	else
		return (NULL);
}
