/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 13:37:26 by okovalov          #+#    #+#             */
/*   Updated: 2018/01/15 17:58:36 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <wchar.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# include <stdint.h>

# define A(x) ((x) < 0 ? -(x) : (x))
# define BIT7 127
# define BIT11 2047
# define BIT16 65535
# define BIT21 2097151

typedef struct	s_prnt
{
	char	tup;
	char	*buf;
	int		shur[2];
	int		tochn[2];
	char	razm;
	char	flg[5];
	char	*temp;
	int		lng;
	int		i;
	int		jj;
}				t_prnt;

int				g_ns;

int				ft_printf(const char *format, ...);
t_prnt			specform(const char *format, int i);
int				cast(t_prnt prf, va_list ap);
void			cinc(t_prnt prf, va_list ap);
void			cins(t_prnt prf, va_list ap);
void			cind(t_prnt prf, va_list ap);
void			cinx(t_prnt prf, va_list ap);
void			cino(t_prnt prf, va_list ap);
void			cinu(t_prnt prf, va_list ap);
void			cinp(t_prnt prf, va_list ap);
void			cinn(t_prnt prf);
void			ft_putstr_pr(char const *s);
char			*ft_itoa_base(unsigned long long value, int base, int flag);
void			ft_putchar_pr(char c);
char			*ft_itoaspec(intmax_t value);
void			put_wstr(char **d);
int				check_len_wchar(char **data);
void			place_wchar(int size, char c);
int				take_wlen(const uint32_t symbol);
char			*parse_wchar(const uint32_t symbol, int p);
void			make_width(char **data, t_prnt prf);
void			widestr(wchar_t *d, t_prnt prf);
uintmax_t		casttype(uintmax_t *tem, t_prnt prf, va_list ap);
void			zero(t_prnt prf, int f);
int				color(const char *format, int i);
void			cind2(t_prnt *prf, va_list ap, intmax_t *tem);
void			cind3(t_prnt prf, intmax_t tem);
int				specform2(const char *format, int i, t_prnt *prf);
int				specform3(const char *format, int i, t_prnt *prf);
int				percent(const char *format, int i, va_list ap);
int				num(const char *format, int i, int *st, t_prnt *prf);
void			wldcr(t_prnt *prf, va_list ap);
int				flag(const char *format, int i, t_prnt *prf);
int				hl(const char *format, int i, t_prnt *prf);
void			normd(t_prnt *prf, va_list ap, intmax_t *tem);
void			minuso(t_prnt prf);
void			minusx(t_prnt prf);

#endif
