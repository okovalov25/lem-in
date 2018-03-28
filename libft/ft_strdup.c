/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:48:54 by okovalov          #+#    #+#             */
/*   Updated: 2016/11/25 16:45:10 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	int		i;
	char	*str;
	int		s;

	i = 0;
	while (s1[i])
		i++;
	s = 0;
	str = malloc(i + 1);
	if (str == 0)
		return (0);
	while (s1[s])
	{
		str[s] = s1[s];
		s++;
	}
	str[s] = '\0';
	return (str);
}
