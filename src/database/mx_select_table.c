#include "uchat.h"

static char *mx_get_request_select(char *n_t, t_table *table, char *cond) {
    char *request = NULL;
    t_table *tmp = table;

    mx_stradd(&request, "SELECT ");
    if (!tmp)
        mx_stradd(&request, "*");
    else
        while(tmp) {
            mx_stradd(&request, tmp->name);
            if (tmp->next)
                mx_stradd(&request, ",");
            mx_stradd(&request, " ");
            tmp = tmp->next;
    }
    mx_stradd(&request, " FROM ");
    mx_stradd(&request, n_t);
    mx_stradd(&request, " ");
    mx_stradd(&request, cond);
    mx_stradd(&request, ";");
    return request;
}

static void mx_get_s_r(sqlite3_stmt *res, int col, t_list_arr **r) {
    int step = 0;
    char *buf = NULL;
    char **tmp = NULL;

    while(1) {
        step = sqlite3_step(res);
        if(step == SQLITE_ROW) {
            tmp = mx_create_char_arr(col);
            for (int i = 0; i < col; i++) {
                sqlite3_column_bytes(res, i);
                buf = (char*)sqlite3_column_text(res, i);
                tmp[i] = mx_strdup(buf);
                buf = NULL;
            }
            mx_arr_push_back(r, tmp);
            mx_del_strarr(&tmp);
        }
        else if (step == SQLITE_DONE)
            break;
    }
}

static int mx_check_open_database(sqlite3 **db, t_database t_db) {
    int res = sqlite3_open(t_db.name_db, db);

    return res;
}

t_list_arr *mx_select_table(const t_database t_db, char *cond, int columns) {
    sqlite3 *db = NULL;
    char *request = mx_get_request_select(t_db.name_table, t_db.table, cond);
    sqlite3_stmt *resp = NULL;
    t_list_arr *response = NULL;

    if (mx_check_open_database(&db, t_db) != SQLITE_OK)
        mx_print_error("Cannot open database", 1, true);
    else {
        sqlite3_prepare_v2(db, request, mx_strlen(request) + 1, &resp, NULL);
        sqlite3_close(db);
        mx_get_s_r(resp, columns, &response);
        return response; 
    }
    mx_strdel(&request);
    return NULL;
}