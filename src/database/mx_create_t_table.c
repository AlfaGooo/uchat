#include "uchat.h"

t_table *mx_create_t_table(char *name, char *params, char *type) {
    t_table *table = (t_table*)malloc(sizeof(t_table));

    table->name = mx_strdup(name);
    table->params = mx_strdup(params);
    table->type = mx_strdup(type);
    table->next = NULL;
    table->data = NULL;
    return table;
}
