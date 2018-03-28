/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 13:58:21 by okovalov          #+#    #+#             */
/*   Updated: 2016/11/28 13:10:33 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 == '\0' && *s2 == '\0')
			return (0);
		else if (*s1 != *s2)
			return ((*(unsigned char*)s1) - (*(unsigned char*)s2));
		s1++;
		s2++;
	}
	return (0);
}
