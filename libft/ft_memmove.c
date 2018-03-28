/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 14:57:34 by okovalov          #+#    #+#             */
/*   Updated: 2016/12/02 13:17:45 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*sorc;
	unsigned char	*dest;

	sorc = (unsigned char *)src;
	dest = (unsigned char *)dst;
	if (dst > src)
		while (len-- > 0)
			dest[len] = sorc[len];
	else
		while (len-- > 0)
			*dest++ = *sorc++;
	return (dst);
}
