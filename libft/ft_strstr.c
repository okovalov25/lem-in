/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:12:17 by okovalov          #+#    #+#             */
/*   Updated: 2016/11/25 14:21:15 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int i;
	int j;

	i = 0;
	if (!*little)
		return ((char*)big);
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j])
		{
			if (!little[j + 1])
				return ((char*)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
