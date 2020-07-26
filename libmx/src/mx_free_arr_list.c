#include "libmx.h"

void mx_free_arr_list(t_list_arr **list) {
    t_list_arr *tmp = *list;
    t_list_arr *last = NULL;
    
    if (!list || !(*list))
        return;
    while(tmp->next) {
        last = tmp;
        tmp = tmp->next;
        mx_del_strarr(&last->data);
        free(last);
        last = NULL;
    }
    mx_del_strarr(&tmp->data);
    free(tmp);
    tmp = NULL;
    *list = NULL;
}
