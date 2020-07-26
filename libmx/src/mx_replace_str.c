#include "libmx.h"

static void mx_replace_str2(char **tmp1, char **tmp2, const char *replace, int k) {
    mx_strdel(tmp2);
    *tmp2 = mx_strndup(*tmp1, k);
    mx_stradd(tmp2, replace);  
}

static void mx_replace_str3(char **tmp1, char **tmp2, char **str) {
    mx_strdel(str);
    *str = mx_strdup(*tmp1);
    mx_strdel(tmp1);
    mx_strdel(tmp2);   
}

void mx_replace_str(char **str, const char *sub, const char *replace) {
    char *tmp1 = NULL;
    char *tmp2 = NULL;
    int k = 0;
    int len_sub = 0;
    
    if (!(*str) || !sub || !replace) 
        return;
    len_sub = mx_strlen(sub);
    tmp1 = mx_strdup(*str);
    while (k >= 0) {
        k = mx_get_substr_index(tmp1, sub);
        if (k == -1)
            break;
        mx_replace_str2(&tmp1, &tmp2, replace, k);
        mx_stradd(&tmp2, &tmp1[len_sub + k]);
        mx_strdel(&tmp1);
        tmp1 = mx_strdup(tmp2); 
    }
    mx_replace_str3(&tmp1, &tmp2, str);
}
