#include "uchat.h"

static void mx_get_request_update2(char **request, char *condition) {
    mx_stradd(request, " ");
    mx_stradd(request, condition);
    mx_stradd(request, ";");   
}

static char *mx_get_request_update(t_database t_db, char *condition) {
    char *request = mx_strdup("UPDATE ");
    t_table *tmp = t_db.table;

    mx_stradd(&request, t_db.name_table);
    mx_stradd(&request, " SET");
    while(tmp) {
        mx_stradd(&request, " ");
        mx_stradd(&request, tmp->name);
        mx_stradd(&request, " = ");
        if (!mx_strcmp("TEXT", tmp->type))
            mx_stradd(&request, "\'");
        mx_stradd(&request, tmp->data);
        if (!mx_strcmp("TEXT", tmp->type))
            mx_stradd(&request, "\'");
        if (tmp->next)
            mx_stradd(&request, ",");
        tmp = tmp->next;
    }
    mx_get_request_update2(&request, condition);
    return request;
}

void mx_update_data(t_database t_db, char *condition) {
    char *request = mx_get_request_update(t_db, condition);
    char *err_msg = 0;
    sqlite3 *db = NULL;
    int res = sqlite3_open(t_db.name_db, &db);

    if (res!= SQLITE_OK) 
        mx_print_error("Cannot open database", 1, true);
    else
        res = sqlite3_exec(db, request, 0, 0, &err_msg);
    if (res != SQLITE_OK) {
        sqlite3_free(err_msg);
        sqlite3_close(db);
        mx_print_error("Error update data", 2, true);
    }
    sqlite3_close(db);  
    mx_strdel(&request); 
}
