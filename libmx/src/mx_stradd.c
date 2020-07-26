#include "libmx.h"

void mx_stradd(char **str, char const *s) {
    int len_str = 0;
    int len_s = 0;
    char *result = NULL;

    if (!(*str))
        *str = mx_strdup(s);
    else if (s) {
        len_str = mx_strlen(*str);
        len_s = mx_strlen(s);
        result = mx_strnew(len_str + len_s);
        for (int i = 0; i < len_str; i++)
            result[i] = (*str)[i];
        for (int i = len_str; i < len_str + len_s; i++)
            result[i] = s[i - len_str];
        mx_strdel(str);
        *str = mx_strdup(result);
        mx_strdel(&result);
    }
}
