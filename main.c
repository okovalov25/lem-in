
#include "lem-in.h"

int valid(t_lmn *lmn)
{
    char *buf;
    int   n;
    char  c;
    int   rez;
    int   i;

    if (get_next_line(0, &buf))
    {
        i = -1;
        while (buf[++i])
            if (ft_isalpha(buf[i]))
                return (0);
        if ((n = ft_atoi(buf)) > 0)
            lmn->nmbr = n;
        else
            return (0);
    }
    free(buf);
    n = -1;
    while (get_next_line(0, &buf))
    {
        ft_lstpushback(&lmn->all, buf, ft_strlen(buf));
        if (buf[0] == '#' && (ft_strcmp(buf, "##start") && ft_strcmp(buf, "##end"))) {
            free(buf);
            continue;
        }
        if ((rez = analyze(buf)) == -1
            || (rez == 1 && n == -1) || (rez == 0 && n == 1))
            return (0);
        else if (rez == 0) {
            n = 0;
            if (!ft_strcmp(buf, "##start") || !ft_strcmp(buf, "##end")) {
                if (!ft_strcmp(buf, "##start"))
                    c = 's';
                else
                    c = 'e';
                free(buf);
                get_next_line(0, &buf);
                ft_lstpushback(&lmn->all, buf, ft_strlen(buf));
                if (buf[0] == 'L' || buf[0] == '#' || analyze(buf) != 0
                    || !ft_strcmp(buf, "##start") || !ft_strcmp(buf, "##end") || !roomfnd(buf, lmn, c))
                    return (0);
            } else {
                if (buf[0] == 'L' || buf[0] == '#' || !roomfnd(buf, lmn, 'o'))
                    return (0);
            }
        }
        else if (rez == 1)
        {
            n = 1;
            if (linkfnd(buf, lmn) < 2)
                return (0);
        }
        free(buf);
    }
    if (lmn->end == -1 || lmn->str == -1 || n != 1)
        return (0);
    return (1);
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

void    compare(t_lmn *lmn, int i)
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
                if (!bg->next)
                    return;
                if (lenfre((t_list *)bg->content, i))
                {
                    if (lenlist(begin->content) < lenlist(bg->content))
                        dellist(((t_list **)&(bg->content)));
                    else
                        dellist(((t_list **)&(begin->content)));
                    return;
                }
                bg = begin->next;
            }
        }
        begin = begin->next;
    }
}

void    filtr(t_lmn *lmn)
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
            compare(lmn, i);
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
                free(begin);
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
    free(g);
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
                if (g->content)
                {
                    c = *((int *) g->content);
                    if (c == a)
                    {
                        g = g->next;
                        c = *((int *) g->content);
                        if (a == lmn->str)
                        {
                            if (lmn->entr == e)
                                return (c);
                        }
                        else
                            return (c);
                    }
                }
                g = g->next;
            }
        }
        begin = begin->next;
        e++;
    }
    return (-1);
}

char*     idtoname(t_lmn *lmn, int i)
{
    t_rms *begin;

    begin = lmn->rms;
    while (begin)
    {
        if (begin->id == i)
            return (begin->name);
        begin = begin->next;
    }
    return (NULL);
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
                printf("L%d-%s ", i + 1, idtoname(lmn, ants[i]));
            }
        }
        printf("\n");
    }
}

void    printin(t_lmn *lmn)
{
    t_list *tmp;

    tmp = lmn->all;
    printf("%d\n", lmn->nmbr);
    while (tmp)
    {
        printf("%s\n", (char*)tmp->content);
        tmp = tmp->next;
    }
    ft_printf("\n");
}

void    printout(t_lmn *lmn)
{
    t_list *g;
    t_list *bg;

    bg = lmn->way;
    ft_printf("\n");
    while (bg)
    {
        g = (t_list *)bg->content;
        while (g)
        {
            int *id = g->content;
            ft_printf("%s ", idtoname(lmn, *id));
            g = g->next;
        }
        ft_printf("\n");
        bg = bg->next;
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
    lmn.str = -1;
    lmn.end = -1;

    if (!valid(&lmn))
    {
        printf("ERROR\n");
        return (0);
    }
    matrix(&lmn);
    recur(&lmn);
    if (!lmn.way->content)
    {
        printf("ERROR\n");
        return (0);
    }
    filtr(&lmn);
    printin(&lmn);
    ant(&lmn);
    if (argc == 2 && !ft_strcmp(argv[1], "way"))
    {
        printout(&lmn);
    }
    while(1);
    return (1);
}
