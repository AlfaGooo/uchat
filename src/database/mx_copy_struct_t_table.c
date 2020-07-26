#include "uchat.h"

t_table *mx_copy_struct_t_table(t_table *table) {
    t_table *copy = NULL;
    t_table *tmp = table;
    
    if(!tmp)
        return NULL;
    while(tmp) {
        mx_push_t_table(&copy, tmp->name, tmp->params, tmp->type);
        tmp = tmp->next;
    }
    return copy;
}
