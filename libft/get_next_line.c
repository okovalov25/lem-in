/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 11:45:26 by okovalov          #+#    #+#             */
/*   Updated: 2017/01/31 15:06:02 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*sschk(char *ss, int i, char **line)
{
	char		*vvd;
	char		*ost;

	if (i > -1)
	{
		vvd = ft_strsub(ss, 0, i);
		ost = ft_strsub(ss, i + 1, ft_strlen(ss));
		*line = vvd;
		free(ss);
		return (ost);
	}
	else
	{
		*line = ss;
		ss = ft_strnew(0);
		return (ss);
	}
}

int				chk(char *str)
{
	int			i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (-1);
}

char			*bloc(char *ss, char *buf)
{
	char		*t;

	t = ss;
	ss = ft_strjoin(ss, buf);
	free(t);
	return (ss);
}

int				get_next_line(const int fd, char **line)
{
	static char	*ss;
	char		*buf;
	int			i;
	int			var;

	if (fd < 0 || !line)
		return (-1);
	if (!ss)
		ss = ft_strnew(0);
	buf = ft_strnew(BUFF_SIZE);
	while ((0 > chk(ss)) && 0 < (var = read(fd, buf, BUFF_SIZE)))
	{
		ss = bloc(ss, buf);
		free(buf);
		buf = ft_strnew(BUFF_SIZE);
	}
	free(buf);
	if (0 <= (i = chk(ss)) || (var == 0 && ft_strlen(ss) > 0))
	{
		ss = sschk(ss, i, line);
		return (1);
	}
	return (var);
}
