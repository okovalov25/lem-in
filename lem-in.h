
#ifndef LEM_IN_H
#define LEM_IN_H

#include "libft/libft.h"

typedef struct  s_rooms
{
    char			*name;
    t_list          *links;
    int             id;
    struct s_rooms	*next;
}               t_rms;

typedef struct  s_lemin
{
    int     nmbr;
    t_rms   *rms;
    t_list  *all;
    int     id;
    int     wid;
    int     str;
    int     end;
    int     **mtrx;
    int     *mtrxv;
    t_list  *way;
}               t_lmn;

void    lstroompush(t_rms **list, char *content, int id);

#endif