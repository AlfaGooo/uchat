#include "uchat.h"

void mx_free_t_table(t_table **table) {
    t_table *tmp = *table;
    t_table *last = NULL;

    while(tmp) {
        last = tmp;
        tmp = tmp->next;
        mx_strdel(&last->name);
        mx_strdel(&last->type);
        mx_strdel(&last->params);
        free(last);
        last = NULL;
    }
}
