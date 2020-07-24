#include "libmx.h"

static int calc_sum(char *mode) {
    int sum = 0;

    if (mx_get_char_index(mode, 'r') >= 0)
        sum += 1;
    if (mx_get_char_index(mode, 'w') >= 0)
        sum += 5;
    if (mx_get_char_index(mode, 'x') >= 0)
        sum += 10;

    return sum;
}

bool mx_create_file(char *file, char *mode) {
    int fd = 0;

    switch (calc_sum(mode)) {
        case 1: fd = open(file, O_CREAT, S_IRUSR); break;
        case 5: fd = open(file, O_CREAT, S_IWUSR); break;
        case 6: fd = open(file, O_CREAT, (S_IRUSR | S_IWUSR)); break;
        case 10: fd = open(file, O_CREAT, S_IXUSR); break;
        case 11: fd = open(file, O_CREAT, (S_IXUSR | S_IRUSR)); break;
        case 15: fd = open(file, O_CREAT, (S_IXUSR | S_IWUSR)); break;
        case 16 : fd = open(file, O_CREAT, S_IRWXU); break;
        default: fd = open(file, O_CREAT, (S_IRUSR | S_IWUSR)); break;
    }

    close(fd);
    if (fd < 3)
        return false;
    return true;
}
