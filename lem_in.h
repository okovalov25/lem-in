/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 14:13:31 by okovalov          #+#    #+#             */
/*   Updated: 2018/08/09 14:21:45 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft/libft.h"

typedef struct	s_rooms
{
	char			*name;
	t_list			*links;
	int				id;
	int				x;
	int				y;
	struct s_rooms	*next;
}				t_rms;

typedef struct	s_coor
{
	char	*name;
	int		x;
	int		y;
}				t_coor;

typedef struct	s_lemin
{
	int		nmbr;
	t_rms	*rms;
	t_list	*all;
	int		id;
	int		wid;
	int		str;
	int		end;
	int		entr;
	int		**mtrx;
	int		*mtrxv;
	int		*vroom;
	t_list	*way;
}				t_lmn;

void			lstroompush(t_rms **list, t_coor *cr, int id);
void			filtr(t_lmn *lmn);
void			printout(t_lmn *lmn);
void			dellist(t_list **list);
t_coor			namecoor(char *buf, t_coor cr);
int				links(t_lmn *lmn, int i, int j);
int				lenfre(t_list *rm, int i);
int				roomfnd(char *buf, t_lmn *lmn, char c);
int				linkfnd(char *buf, t_lmn *lmn);
int				analyze(char *buf);
void			printin(t_lmn *lmn);
char			*idtoname(t_lmn *lmn, int i);
void			ant(t_lmn *lmn);
int				moveant(int a, t_lmn *lmn);
void			matrix(t_lmn *lmn);
int				lenlist(t_list *list);
void			recur(t_lmn *lmn);
void			compare(t_lmn *lmn, int i);
int				valid(t_lmn *lmn);

#endif
