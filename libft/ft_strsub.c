/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:16:06 by okovalov          #+#    #+#             */
/*   Updated: 2016/12/02 13:26:21 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned long	a;
	char			*d;

	if (!s)
		return (NULL);
	a = 0;
	d = (char *)malloc(sizeof(char) * len + 1);
	if (d)
	{
		while (a < len)
			d[a++] = s[start++];
		d[a] = '\0';
		return (d);
	}
	else
		return (NULL);
}
