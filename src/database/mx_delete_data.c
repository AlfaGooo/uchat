#include "uchat.h"

static char *mx_get_request_delete(t_database t_db, char *condition) {
    char *request = mx_strdup("DELETE FROM ");

    mx_stradd(&request, t_db.name_table);
    mx_stradd(&request, " ");
    mx_stradd(&request, condition);
    mx_stradd(&request, ";");
    return request;
}

void mx_delete_data(t_database t_db, char *condition) {
    char *request = mx_get_request_delete(t_db, condition);
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
        mx_print_error("Error delete data", 2, true);
    }
    sqlite3_close(db);
    mx_strdel(&request);
}
