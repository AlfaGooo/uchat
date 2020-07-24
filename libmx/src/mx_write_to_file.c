#include "libmx.h"

static int len_file_append(const char *str_from_file, const char *str) {
    if (!str_from_file && str)
        return mx_strlen(str);
    else if (str_from_file && !str)
        return mx_strlen(str_from_file);
    else if (!str_from_file && !str)
        return 0;
    else
        return mx_strlen(str_from_file) + mx_strlen(str);
}

static bool create_file_append(const char *file, const char *str) {
    char *str_from_file = NULL;
    char *temp = NULL;
    int fd = open(file, O_WRONLY);
    int write_index = 0;
    int len = 0;

    if (fd != -1) {
        temp = mx_file_to_str(file);
        str_from_file = mx_strjoin(temp, str);
        len = len_file_append(str_from_file, str);
        write_index = write(fd, str_from_file, len);
        mx_strdel(&str_from_file);
        mx_strdel(&temp);
    }
    else
        return false;
    close(fd);
    if (write_index != len)
        return false;
    return true;
}

bool mx_write_to_file(const char *file, const char *str, char mode) {
    int fd = -1;
    int write_index = 0;
    int len_str = 0;

    if (str)
        len_str = mx_strlen(str);
    if (mode == 'w')
        fd = open(file, O_WRONLY);
    else if (mode == 'a')
        return create_file_append(file, str);
    if (fd != -1)
        write_index = write(fd, str, len_str);
    else
        return false;
    close(fd);
    if (write_index != len_str)
        return false;
    return true;
}
