/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:58:32 by okovalov          #+#    #+#             */
/*   Updated: 2016/12/03 11:25:00 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little)
		return ((char*)big);
	while (big[i])
	{
		j = 0;
		if (!len)
			return (NULL);
		while ((big[i + j] == little[j]) && (len - 1) >= j)
		{
			if (!little[j + 1])
				return ((char*)big + i);
			j++;
		}
		len--;
		i++;
	}
	return (NULL);
}
