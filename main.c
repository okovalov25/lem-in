
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
        else
            return (0);

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
                if (!ft_strcmp(buf, "##start"))
                    c = 's';
                else
                    c = 'e';
                get_next_line(0, &buf);
                ft_lstpushback(&lmn->all, buf, ft_strlen(buf));
                if (buf[0] == 'L' || buf[0] == '#')
                    return (0);
                roomfnd(buf, lmn, c);
                if (ft_strchr(buf, '-'))
                    n = 1;
            }
            else
            {
                if (ft_strchr(buf, '-'))
                    n = 1;
                else
                {
                    if (buf[0] == 'L' || buf[0] == '#')
                        return (0);
                    roomfnd(buf, lmn, 'o');
                }
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
            lnk = tmp->links;
            while (lnk)
            {
                tmp = lmn->rms;
                while (tmp)
                {
                    if (tmp->id == i && !ft_strcmp(lnk->content, tmp->name))
                        return (1);
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
    lmn->vroom = (int *)malloc(sizeof(int) * lmn->id + 1);
    while (++j <= lmn->id)
    {
        i = -1;
        lmn->mtrx[j] = (int *)malloc(sizeof(int) * lmn->id + 1);

        while (++i <= lmn->id)
        {
            lmn->mtrxv[i] = 0;
            lmn->vroom[i] = 0;
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
    int r;

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
                r = findway(lmn, j, begin);
                return (r);
            }
        }
    }
    return (0);
}

void    recur(t_lmn *lmn)
{
    t_list *begin;
    int i;
    int j;

    i = -1;
    begin = ft_lstnew(NULL, 0);
    lmn->way = begin;
    while (++i <= lmn->id)
    {
        if (lmn->mtrx[lmn->str][i] == 1)
        {
            lmn->mtrxv[lmn->str] = 1;
            if (i == lmn->end)
            {
                ft_lstpushback((t_list **)&begin->content, &lmn->str, sizeof(int));
                ft_lstpushback((t_list **)&begin->content, &lmn->end, sizeof(int));
                begin->next = ft_lstnew(NULL, 0);
                begin = begin->next;
                lmn->wid++;
            }
            else
            {
                lmn->mtrxv[i] = 1;
                if (findway(lmn, i, begin))
                {
                    ft_lstadd((t_list **)&begin->content, ft_lstnew(&i, sizeof(int)));
                    ft_lstadd((t_list **)&begin->content, ft_lstnew(&lmn->str, sizeof(int)));
                    begin->next = ft_lstnew(NULL, 0);
                    begin = begin->next;
                    lmn->wid++;
                }
                else
                    free(begin->content);
            }
        }
        j = 0;
        while (j <= lmn->id)
        {
            lmn->vroom[j] += lmn->mtrxv[j];
            lmn->mtrxv[j] = 0;
            j++;
        }
    }
    begin->content = NULL;
    lmn->vroom[lmn->str] = 0;
    filtr(lmn, begin);
}

int     lenlist(t_list *list)
{
    int i;

    i= 0;
    while (list)
    {
        i++;
        list = list->next;
    }
    return (i);
}

void    dellist(t_list **list)
{
    t_list *tmp;
    t_list *next;

    tmp = *list;
    while (tmp)
    {
        next = tmp->next;
        if (tmp->content)
            free(tmp->content);
        free(tmp);
        tmp = next;
    }
    *list = NULL;
}

int   lenfre(t_list *rm, int i)
{
    int *id;

    while (rm)
    {
        id = rm->content;
        if (*id == i)
            return (1);
        rm = rm->next;
    }
    return (0);
}

void    compare(t_lmn *lmn, t_list *way, int i)
{
    t_list *begin;
    t_list *bg;

    begin = lmn->way;
    while (begin)
    {
        if (lenfre((t_list *)begin->content, i))
        {
            bg = begin->next;
            while (bg)
            {
                if (lenfre((t_list *)bg->content, i))
                {
                    if (lenlist(begin->content) < lenlist(bg->content))
                    {
                        dellist(bg->content);
                        free(bg);
                        return;
                    }
                    else
                    {
                        dellist(begin->content);
                        free(begin);
                        return;
                    }
                }
                bg = begin->next;
            }
        }
        begin = begin->next;
    }
}

void    filtr(t_lmn *lmn, t_list *way)
{
    int i;
    t_list *begin;
    t_list *g;
    t_list *n;


    i = -1;
    while (++i <= lmn->id)
    {
        if (lmn->vroom[i] >= 2)
        {
            compare(lmn, way, i);
            lmn->vroom[i]--;
            i = -1;
        }
    }
    begin = lmn->way;
    g = NULL;
    while (lmn->way)
    {
        if (!lmn->way->content)
        {
            if (!g)
            {
                g = lmn->way->next;
                lmn->way->next = NULL;
                lmn->way = g;
                begin = g;
            }
            else
            {
                if (lmn->way->next)
                {
                    n = lmn->way->next;
                    lmn->way->next = NULL;
                    g->next = n;
                }
                else
                {
                    g->next = NULL;
                }
            }
        }
        g = lmn->way;
        lmn->way = lmn->way->next;
    }
    lmn->way = begin;
}

int    antcheck(int *ants, int n, int end)
{
    int i;

    i = -1;
    while (++i < n)
        if (ants[i] != end)
            return (0);
    return (1);
}

int     moveant(int a, t_lmn *lmn)
{
    t_list *g;
    t_list *begin;
    int     e;
    int     c;

    e = 0;
    if (a == lmn->str)
        lmn->entr++;
    begin = lmn->way;
    while (begin)
    {
        if (begin->content)
        {
            g = (t_list *)begin->content;
            while (g)
            {
                c = *((int *)g->content);
                if (c == a)
                {
                    g = g->next;
                    c = *((int *)g->content);
                    if (a == lmn->str)
                    {
                        if (lmn->entr == e)
                            return (c);
                    }
                    else
                        return (c);
                }
                g = g->next;
            }
        }
        begin = begin->next;
        e++;
    }
    return (-1);
}

void    ant(t_lmn *lmn)
{
    int *ants;
    int i;
    int r;

    i = -1;
    ants = (int *)malloc(sizeof(int) * lmn->nmbr - 1);
    while (++i < lmn->nmbr)
        ants[i] = lmn->str;
    while (!antcheck(ants, lmn->nmbr, lmn->end))
    {
        lmn->entr = -1;
        i = -1;
        while (++i < lmn->nmbr)
        {
            if (ants[i] == lmn->end)
                continue;
            r = moveant(ants[i], lmn);
            if (r > -1)
            {
                ants[i] = r;
                printf("L%d-%d ", i + 1, ants[i]);
            }
        }
        printf("\n");
    }

}

void    printin(t_lmn *lmn)
{
    printf("%d\n", lmn->nmbr);
    while (lmn->all)
    {
        if (lmn->all)
            printf("%s\n", (char*)lmn->all->content);
        lmn->all = lmn->all->next;
    }
    ft_printf("\n");
}

void    printout(t_lmn *lmn)
{
    t_list *g;

    printf("\n");
    while (lmn->way)
    {
        if (lmn->way)
        {
            g = (t_list *) lmn->way->content;
            while (g)
            {
                int *id = g->content;
                printf("%d ", *id);
                g = g->next;
            }
            printf("\n");
        }
        lmn->way = lmn->way->next;
    }
}

int main(int argc, char **argv)
{
    t_lmn lmn;

    lmn.all = NULL;
    lmn.rms = NULL;
    lmn.way = NULL;
    lmn.id = -1;
    lmn.wid = 0;

    if (!valid(&lmn))
    {
        printf("ERROR\n");
        return (0);
    }
    matrix(&lmn);
    recur(&lmn);
    printin(&lmn);
    ant(&lmn);

    if (argc == 2 && !ft_strcmp(argv[1], "way"))
        printout(&lmn);
    return (1);
}
