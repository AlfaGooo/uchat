#include "uchat.h"

void mx_push_t_table(t_table **table, char *name, char *params, char *type) {
    t_table *tmp = *table;

    if (!tmp) 
        *table = mx_create_t_table(name, params, type);
    else {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = mx_create_t_table(name, params, type);
    }
}
