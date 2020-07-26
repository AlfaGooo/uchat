#include "uchat.h"

static char *mx_get_requst_create_table(t_database t_db) {
    t_table *tmp = t_db.table;
    char *request = mx_strjoin("CREATE TABLE ", t_db.name_table);

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
    return request;    
}

void mx_create_table(const t_database t_db) {
    char *err_msg = 0;
    sqlite3 *db = NULL;
    char *request = mx_get_requst_create_table(t_db);
    int res = sqlite3_open(t_db.name_db, &db);

    if (res!= SQLITE_OK)
        mx_print_error("Cannot open database", 1, true);
    else
        res = sqlite3_exec(db, request, 0, 0, &err_msg);
    if (res != SQLITE_OK) {
        mx_print_error("Error create table", 1, true);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }
    sqlite3_close(db);
    mx_strdel(&request);
}
