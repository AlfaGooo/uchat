#include <sqlite3.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include "libmx.h"

#define DATABASE_NAME "database.db"

typedef struct s_user {
    char *login;
    char *password;
    char *email;
    struct s_user *next;
} t_user;

typedef struct s_table {
    char *name;
    char *params;
    char *type;
    char *data;
    struct s_table *next;
} t_table;

typedef struct s_sql_resp {
    char **data;
    struct s_sql_resp *next;
} t_sql_resp;

t_sql_resp *mx_select_table(char const *name_db, char const *name_table, sqlite3 **db, t_table *table, char *condition, int columns) {
    int res_open = sqlite3_open(name_db, db);
    t_table *tmp = table;
    char *request = NULL;
    sqlite3_stmt *response = NULL;
    t_sql_resp *result = NULL;
    int step = 0;
    int row;
    char **tmp_arr = NULL;

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
    mx_stradd(&request, name_table);
    mx_stradd(&request, " ");
    mx_stradd(&request, condition);
    mx_stradd(&request, ";");
    
    sqlite3_open(name_db, db);
    sqlite3_prepare_v2(*db, request, mx_strlen(request) + 1, &response, NULL);

    while(1) {
        step = sqlite3_step(response);
        tmp_arr = mx_create_char_arr(columns);
        if(step == SQLITE_ROW) {
            for (int i = 0; i < columns; i++) {
                sqlite3_column_bytes (response, i);
                tmp_arr[i] = (char*)sqlite3_column_text(response, i);
            }
            mx_push_sql_resp(&result, tmp_arr);
        }
        else if (step == SQLITE_DONE)
            break;
        mx_push_sql_resp(&result, tmp_arr);
        mx_del_strarr(&tmp_arr);
    }
    return result;
}

void mx_print_sql_resp(t_sql_resp *resp) {
    t_sql_resp *tmp = resp;

    while(tmp) {
        mx_print_strarr(tmp->data, " | ");
        tmp = tmp->next;
    }
}

typedef struct s_sql_resp {
    char **data;
    struct s_sql_resp *next;
} t_sql_resp;


bool mx_sql_add_user_to_room(int room_id, int user_id) {
    sqlite3 *db = NULL;
    t_table *column = NULL;
    t_sql_resp *res_u = NULL;
    t_sql_resp *res_r = NULL;

    res_u = mx_select_table(DATABASE_NAME, "users", &db, column, user_id, 4); //пятым параметром указываем условие Например "WHERE ID=1", шестой параметр - количество столбцов в таблице В данной таблице и две - id, login
    res_r = mx_select_table(DATABASE_NAME, "room", &db, column, room_id, 2); //пятым параметром указываем условие Например "WHERE ID=1", шестой параметр - количество столбцов в таблице В данной таблице и две - id, login

    if (res_u == NULL || res_r == NULL)
        return false;
    
    mx_push_t_table(&column, "room_id", "PRIMARY KEY", "INTEGER");
    mx_push_t_table(&column, "user_id", "PRIMARY KEY", "INTEGER");

    mx_push_data_table(&column, &res_r); //добавляем в структуру колонок реквизит с данными по каждой колонке
    mx_insert_data(DATABASE_NAME, "users_room", &db, column);

    mx_push_data_table(&column, &res_u); //добавляем в структуру колонок реквизит с данными по каждой колонке
    mx_insert_data(DATABASE_NAME, "users_room", &db, column);

    return true;
}
