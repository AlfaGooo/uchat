#include "libmx.h"

int mx_file_len(const char *file) {
    int fd = open(file, O_RDONLY);
    char buf;
    int len = 0;

    if (fd != -1) {
        while(read(fd, &buf, 1)) {
            if (!buf)
                return 0;
            len++;
        }
    }
    else
        return -1;
    close(fd);
    return len;
}
