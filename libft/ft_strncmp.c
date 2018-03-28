/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:53:38 by okovalov          #+#    #+#             */
/*   Updated: 2016/12/03 12:12:58 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n)
	{
		if (!*s1 && !*s2)
			return (0);
		else if (*s1 != *s2)
			return ((*(unsigned char*)s1) - (*(unsigned char*)s2));
		s1++;
		s2++;
		n--;
	}
	return (0);
}
