#include "libmx.h"

char **mx_arrdup(char **data) {
    int size = 0;
    char **tmp = NULL;
  
    if (!data)
      return NULL;
    size = mx_arr_size(data);
    tmp = mx_create_char_arr(size);
    for (int i = 0; data[i]; i++)
        tmp[i] = mx_strdup(data[i]);
    return tmp;
}
