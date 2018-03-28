/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:06:13 by okovalov          #+#    #+#             */
/*   Updated: 2016/11/29 11:20:14 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j] && (i + 1) < size)
		dst[i++] = src[j++];
	dst[i] = '\0';
	if (!j)
		i = size;
	while (src[j++])
		i++;
	return (i);
}
