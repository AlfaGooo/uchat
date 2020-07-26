#include "libmx.h"

int mx_arr_size(char **arr) {
    int size = 0;
    
    if (!arr)
        return 0;
        
    for(int i = 0; arr[i]; i++)
        size++;
    return size;
}
