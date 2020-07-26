#include "libmx.h"

void mx_arr_push_back(t_list_arr **arr_list, char **data) {
    t_list_arr *back = mx_create_list_arr(data);
    t_list_arr *tmp = *arr_list;
    
    if (*arr_list == NULL) {
        *arr_list = back;
        return;
    }
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = back;
}
