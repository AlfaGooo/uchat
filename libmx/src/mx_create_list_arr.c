#include "libmx.h"

t_list_arr *mx_create_list_arr(char **data) {
    t_list_arr *tmp = malloc(sizeof(t_list_arr));
    
    tmp->data = mx_arrdup(data);
    tmp->next = NULL;
    return tmp;
}
