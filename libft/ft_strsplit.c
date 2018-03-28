/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 11:45:15 by okovalov          #+#    #+#             */
/*   Updated: 2016/12/10 12:10:52 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_mlcfld(char **d, const char *s, char c)
{
	int			a;
	int			count;

	a = 0;
	count = 0;
	while (s[a])
	{
		if (s[a] != c)
		{
			count++;
			while (s[a] != c && s[a])
				a++;
		}
		else
			a++;
	}
	d = (char**)malloc(sizeof(char*) * (count + 1));
	if (count == 0 && s[0] == '\0')
		count++;
	if (!d)
		return (NULL);
	return (d);
}

static char		**ft_mlcstr(char **d, const char *s, char c)
{
	int			a;
	int			count;
	int			i;

	a = 0;
	count = 0;
	i = 0;
	while (s[a] == c)
		a++;
	while (s[a++])
	{
		count++;
		if (s[a] == c)
		{
			d[i++] = ft_strnew(count);
			count = 0;
			while (s[a] == c)
				a++;
		}
	}
	if ((s[a - 1] != c && count > 0) || (i == 0 && s[0] == '\0'))
		d[i++] = ft_strnew(count);
	d[i] = NULL;
	return (d);
}

static char		**ft_filld(char **d, const char *s, char c)
{
	int			a;
	int			i;
	int			j;

	a = 0;
	i = 0;
	j = 0;
	while (s[a] == c)
		a++;
	if (!s[a])
		return (d);
	while (s[a])
	{
		d[i][j++] = s[a++];
		if (s[a] == c)
		{
			i++;
			j = 0;
			while (s[a] == c)
				a++;
		}
	}
	return (d);
}

char			**ft_strsplit(const char *s, char c)
{
	char		**d;

	if (!s)
		return (NULL);
	if (c == '\0')
	{
		d = (char**)malloc(sizeof(char*) * 2);
		d[0] = (char*)malloc(sizeof(char) * ft_strlen(s) + 1);
		d[0] = (char*)s;
		d[1] = (char*)malloc(sizeof(char) * 1);
		d[1] = NULL;
		return (d);
	}
	d = NULL;
	d = ft_mlcfld(d, s, c);
	if (!d)
		return (NULL);
	d = ft_mlcstr(d, s, c);
	if (!d)
		return (NULL);
	if (s[0] == '\0' && c != '\0')
		d[0] = NULL;
	else
		d = ft_filld(d, s, c);
	return (d);
}
