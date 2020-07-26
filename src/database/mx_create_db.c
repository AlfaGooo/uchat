#include "uchat.h"

void mx_create_db(char const *name_db) {
    int fd = open(name_db, O_WRONLY | O_CREAT | O_TRUNC, 0600);

    if (!fd)
        mx_print_error("Error create database", 2, true);
}
