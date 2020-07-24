#include "libmx.h"

char *mx_file_to_str(const char *file) {
    int len = 0;
    int fd = 0;
    char *str = NULL;

    len = mx_file_len(file);
    if (len == 0)
        return NULL;
    str = mx_strnew(len);
    fd = open(file, O_RDONLY);
    if (fd != -1)
        read(fd, str, len);
    else
        return NULL;
    close(fd);
    return str;
}
