
#include "lem-in.h"

void    roomfnd(char *buf, t_lmn *lmn, char c)
{
    int i;
    char *t;
    t_rms *tmp;

    i = 0;
    lmn->id++;
    while (buf[i] != ' ')
        i++;
    t = ft_strsub(buf, 0, i);
    lstroompush(&lmn->rms, t, lmn->id);
    i = 0;
    if (c == 's' || c == 'e')
    {
        tmp = lmn->rms;
        while (tmp->next)
        {
            if (tmp->name == t)
                ft_lstpushback(&tmp->links, (c == 's' ? "start" : "end!!"), 6);
            tmp = tmp->next;
            i++;
        }
        if (c == 's')
            lmn->str = lmn->id;
        else
            lmn->end = lmn->id;
    }
}

void    linkfnd(char *buf, t_lmn *lmn)
{
    int i;
    char *t;
    char *l;
    t_rms *tmp;

    i = 0;
    while (buf[i] != '-')
        i++;
    t = ft_strsub(buf, 0, i);
    l = ft_strsub(buf, i + 1, ft_strlen(buf));
    tmp = lmn->rms;
    while (tmp)
    {
        if (!ft_strcmp(tmp->name, t))
        {
            ft_lstpushback(&tmp->links, l, ft_strlen(l));
        }
        tmp = tmp->next;
    }
    tmp = lmn->rms;
    while (tmp)
    {
        if (!ft_strcmp(tmp->name, l))
        {
            ft_lstpushback(&tmp->links, t, ft_strlen(t));
        }
        tmp = tmp->next;
    }
}

int valid(t_lmn *lmn)
{
    char *buf;
    int   n;
    char  c;

    if (get_next_line(0, &buf))
        if ((n = ft_atoi(buf)) > 0)
            lmn->nmbr = n;
    n = 0;
    while (get_next_line(0, &buf))
    {
        ft_lstpushback(&lmn->all, buf, ft_strlen(buf));
        if (buf[0] == '#' && buf[1] != '#')
            continue;
        if (n == 0)
        {
            if (!ft_strcmp(buf, "##start") || !ft_strcmp(buf, "##end"))
            {
                ft_lstpushback(&lmn->all, buf, ft_strlen(buf));
                if (!ft_strcmp(buf, "##start"))
                    c = 's';
                else
                    c = 'e';
                get_next_line(0, &buf);
                if (buf[0] == '#' && buf[1] != '#')
                    continue;
                roomfnd(buf, lmn, c);
                if (ft_strchr(buf, '-'))
                    n = 1;
            }
            else
            {
                if (ft_strchr(buf, '-'))
                    n = 1;
                else
                    roomfnd(buf, lmn, 'o');
            }
        }
        if (n == 1)
        {
            linkfnd(buf, lmn);
        }
    }
    return (1);
}

int     links(t_lmn *lmn, int i, int j)
{
    t_rms   *tmp;
    t_list  *lnk;

    tmp = lmn->rms;
    while (tmp)
    {
        if (tmp->id == j)
        {
            //ft_printf("[%s|%d]\n", tmp->name, tmp->id);
            lnk = tmp->links;
            while (lnk)
            {
                tmp = lmn->rms;
                while (tmp)
                {
                    if (tmp->id == i && !ft_strcmp(lnk->content, tmp->name))
                    {
                       // ft_printf("{%s|%d}\n", tmp->name, tmp->id);
                        return (1);
                    }
                    tmp = tmp->next;
                }
                lnk = lnk->next;
            }
            return (0);
        }
        tmp = tmp->next;
    }
    return (0);
}

void    matrix(t_lmn *lmn)
{
    int j;
    int i;

    j = -1;
    lmn->mtrx = (int **)malloc(sizeof(int *) * lmn->id + 1);
    lmn->mtrxv = (int *)malloc(sizeof(int) * lmn->id + 1);
    while (++j <= lmn->id)
    {
        i = -1;
        lmn->mtrx[j] = (int *)malloc(sizeof(int) * lmn->id + 1);

        while (++i <= lmn->id)
        {
            lmn->mtrxv[i] = 0;
            lmn->mtrxv[lmn->str] = 1;
            if (i == j)
                lmn->mtrx[j][i] = 0;
            else if (links(lmn ,j, i))
                lmn->mtrx[j][i] = 1;
            else
                lmn->mtrx[j][i] = 0;
        }
    }
}

int    findway(t_lmn *lmn, int i, t_list *begin)
{
    int j;

    j = -1;
    if (lmn->mtrx[i][lmn->end] == 1)
    {
        ft_lstpushback((t_list **)&begin->content, &lmn->end, sizeof(int));
        return (1);
    }
    while (++j <= lmn->id)
    {
        if (lmn->mtrx[i][j] == 1)
        {
            if (lmn->mtrxv[j] == 1)
                continue;
            else if (lmn->mtrxv[j] == 0)
            {
                lmn->mtrxv[j] = 1;
                ft_lstpushback((t_list **)&begin->content, &j, sizeof(int));
                findway(lmn, j, begin);
                return (1);
            }
        }
    }
    return (0);
}

void    recur(t_lmn *lmn)
{
    t_list *begin;
    int i;

    i = -1;
    begin = ft_lstnew(NULL, 0);
    lmn->way = begin;
    while (++i <= lmn->id)
    {
        if (lmn->mtrx[lmn->str][i] == 1)
        {
            lmn->mtrxv[i] = 1;
            ft_lstpushback((t_list **)&begin->content, &lmn->str, sizeof(int));
            ft_lstpushback((t_list **)&begin->content, &i, sizeof(int));
            if (i != lmn->end)
                findway(lmn, i, begin);
            begin->next = ft_lstnew(NULL, 0);
            begin = begin->next;
            lmn->wid++;
        }
    }
    begin->content = NULL;
}

int main(void) {
    t_lmn lmn;

    lmn.all = NULL;
    lmn.rms = NULL;
    lmn.way = NULL;
    lmn.id = -1;
    lmn.wid = 0;

    valid(&lmn);
    matrix(&lmn);
    recur(&lmn);

    int i = -1;
    ft_printf("\n\\ 01234\n");
    while (++i <= lmn.id) {
        int j = -1;
        ft_printf("%d|", i);
        while (++j <= lmn.id)
            ft_printf("%d", lmn.mtrx[i][j]);
        ft_printf("\n");
    }
    ft_printf("s%d-e%d\n", lmn.str, lmn.end);

    //ft_printf("[%d]\n", lmn.nmbr);

//    while (lmn.rms)
//    {
//        ft_printf("%s|%d\n", lmn.rms->name, lmn.rms->id);
//        while (lmn.rms->links)
//        {
//            ft_printf("{%s}", lmn.rms->links->content);
//            lmn.rms->links = lmn.rms->links->next;
//        }
//        ft_printf("\n");
//        lmn.rms = lmn.rms->next;
//    }

    t_list *g;
    while (lmn.way->next)
    {
        g = (t_list *)lmn.way->content;
        while(g)
        {
            int *id = g->content;
            printf("%d ", *id);
            g = g->next;
        }
        printf("\n");
        lmn.way = lmn.way->next;
    }
    return (1);
}
