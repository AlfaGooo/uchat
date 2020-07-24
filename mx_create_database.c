#include <sqlite3.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include "libmx.h"

#define DATABASE_NAME "database.db"

typedef struct s_table {
    char *name;
    char *params;
    char *type;
    char *data;
    struct s_table *next;
} t_table;

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

static void mx_create_table(char const *name_db, char const *name_table, sqlite3 **db, t_table *table) {
    int res = sqlite3_open(name_db, db);
    char *err_msg = 0;

    t_table *tmp = table;
    char *request = mx_strjoin("CREATE TABLE ", name_table);

    mx_stradd(&request, " (");
    while(tmp) {
        mx_stradd(&request, tmp->name);
        mx_stradd(&request, " ");
        mx_stradd(&request, tmp->type);
        mx_stradd(&request, " ");
        mx_stradd(&request, tmp->params);
        if (tmp->next)
            mx_stradd(&request, ", ");
        tmp = tmp->next;
    }
    mx_stradd(&request, ");");
    mx_printstr(request);
    mx_printchar('\n');
    if (res!= SQLITE_OK)
        mx_print_error("Cannot open database", 1, true);
    else
        res = sqlite3_exec(*db, request, 0, 0, &err_msg);
    if (res != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(*db);
        return;
    }
    sqlite3_close(*db);
}

t_table *mx_create_t_table(char *name, char *params, char *type) {
    t_table *table = (t_table*)malloc(sizeof(t_table));

    table->name = name;
    table->params = params;
    table->type = type;
    table->next = NULL;
    table->data = NULL;
    return table;
}

void mx_push_t_table(t_table **table, char *name, char *params, char *type) {
    t_table *tmp = *table;

    if (!tmp) 
        *table = mx_create_t_table(name, params, type);
    else {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = mx_create_t_table(name, params, type);
    }
}

static bool check_db() {
    int fd = 0;

    fd = open(DATABASE_NAME, O_RDONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) 
        return true;
    return false;
}

//data.db
bool mx_create_database(void ) {
    t_table *column_u = NULL;
    t_table *column_r = NULL;
    t_table *column_u_r = NULL;
    sqlite3 *db = NULL;

    if (check_db())
        return true;
    mx_push_t_table(&column_u, "id", "PRIMARY KEY", "INTEGER"); //table users
    mx_push_t_table(&column_u, "login", NULL, "TEXT");
    mx_push_t_table(&column_u, "password", NULL, "TEXT");
    mx_push_t_table(&column_u, "email", NULL, "TEXT");
    mx_push_t_table(&column_r, "id", "PRIMARY KEY", "INTEGER"); //table room
    mx_push_t_table(&column_r, "name", NULL, "TEXT");
    mx_push_t_table(&column_u_r, "room_id", NULL, "INTEGER"); //table user_room
    mx_push_t_table(&column_u_r, "user_id", NULL, "INTEGER");
    mx_create_table(DATABASE_NAME, "users", &db, column_u);
    mx_create_table(DATABASE_NAME, "room", &db, column_r);
    mx_create_table(DATABASE_NAME, "users_room", &db, column_u_r);
    // system("leaks a.out");
    //free //to write

    return true;
}

int main (int argc, char *argv[]) {
    mx_create_database();
}
