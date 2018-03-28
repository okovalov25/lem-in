/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:05:08 by okovalov          #+#    #+#             */
/*   Updated: 2016/12/07 13:45:59 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*d;

	if (!s || !f)
		return (NULL);
	i = 0;
	d = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (d)
	{
		while (s[i])
		{
			d[i] = f(i, s[i]);
			i++;
		}
		d[i] = '\0';
		return (d);
	}
	else
		return (NULL);
}
