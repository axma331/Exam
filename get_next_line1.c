#include "get_next_line.h"

int get_nex_line(char **line)
{
    int i;
    int l;
    int r;
    char c;
    char *tmp;

    r = 0;
    l = 1;
    if (!(*line = malloc(l)))
        return (-1);
    (*line)[0] = 0;
    while ((r = read(0, &c, 1)) && l++ && c != '\n')
    {
        if (!(tmp = malloc(l)))
        {
            free(*line);
            return (-1);
        }
        i = -1;
        while (++i < l - 2)
            tmp[i] = (*line)[i];
        tmp[i] = c;
        tmp[i + 1] = 0;
        free(*line);
        *line = tmp;     
    }
    return (r);
}