/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:53:32 by okovalov          #+#    #+#             */
/*   Updated: 2016/11/28 14:40:27 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memalloc(size_t size)
{
	char			*d;
	int				i;

	i = 0;
	d = (char *)malloc(sizeof(char) * size);
	if (d)
	{
		while (size--)
		{
			d[i++] = 0;
		}
		d[i] = '\0';
		return (d);
	}
	else
		return (NULL);
}
