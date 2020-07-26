#include "uchat.h"

static void mx_get_request_insert2(char **request, t_table *tmp) {
    while(tmp) {
        if (!mx_strcmp("TEXT", tmp->type))
            mx_stradd(request, "\'");
        mx_stradd(request, tmp->data);
        if (!mx_strcmp("TEXT", tmp->type))
            mx_stradd(request, "\'");
        if (tmp->next)
            mx_stradd(request, ", ");
        tmp = tmp->next;
    }
    mx_stradd(request, ");");	
}

static char *mx_get_request_insert(const t_database t_db) {
    char *request = mx_strjoin("INSERT INTO ", t_db.name_table);
    t_table *tmp = t_db.table;

    mx_stradd(&request, " (");
    while(tmp) {
        mx_stradd(&request, tmp->name);
        if (tmp->next)
            mx_stradd(&request, ", ");
        tmp = tmp->next;
    }
    mx_stradd(&request, ") VALUES (");
    tmp = t_db.table;
    mx_get_request_insert2(&request, tmp);
    return request; 
}

void mx_insert_data(const t_database t_db) {
    char *err_msg = 0;
    char *request = mx_get_request_insert(t_db);
    sqlite3 *db = NULL;
    int res = sqlite3_open(t_db.name_db, &db);

    if (res!= SQLITE_OK) 
        mx_print_error("Cannot open database", 1, true);
    else
        res = sqlite3_exec(db, request, 0, 0, &err_msg);
    if (res != SQLITE_OK) {
        sqlite3_free(err_msg);
        sqlite3_close(db);
        mx_print_error("Error insert data", 2, true);
    }
    sqlite3_close(db);  
    mx_strdel(&request); 
}
