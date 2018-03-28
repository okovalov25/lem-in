/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:20:44 by okovalov          #+#    #+#             */
/*   Updated: 2016/12/06 12:31:01 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	int			a;
	int			i;
	size_t		rez;
	char		*d;

	if (!s1 || !s2)
		return (NULL);
	a = 0;
	i = 0;
	rez = ft_strlen(s1) + ft_strlen(s2);
	d = (char *)malloc(sizeof(char) * rez + 1);
	if (d)
	{
		while (s1[i])
			d[a++] = s1[i++];
		i = 0;
		while (s2[i])
			d[a++] = s2[i++];
		d[a] = '\0';
		return (d);
	}
	else
		return (NULL);
}
