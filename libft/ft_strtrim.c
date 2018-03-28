/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 14:19:36 by okovalov          #+#    #+#             */
/*   Updated: 2016/12/02 13:18:53 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*d;
	int		len;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	j = (int)ft_strlen(s) - 1;
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	len = j - i + 1;
	if (i > 0 && !s[i])
		len = 0;
	j = 0;
	d = (char*)malloc(sizeof(char) * (len + 1));
	if (!d)
		return (NULL);
	while (len--)
		d[j++] = s[i++];
	d[j] = '\0';
	return (d);
}
