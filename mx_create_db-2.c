#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "uchat.h"


// typedef struct s_table {
//     char *name;
//     char *params;
//     char *type;
//     char *data;
//     struct s_table *next;
// } t_table;

// typedef struct s_database {
//     char *name_db;
//     char *name_table;
//     t_table *table;
// } t_database;

// void mx_free_t_table(t_table **table);

// void mx_create_db(char const *name_db) {
//     int fd = open(name_db, O_WRONLY | O_CREAT | O_TRUNC, 0600);

//     if (!fd)
//         mx_print_error("Error create database", 2, true);
// }

// static char *mx_get_requst_create_table(t_database t_db) {
//     t_table *tmp = t_db.table;
//     char *request = mx_strjoin("CREATE TABLE ", t_db.name_table);

//     mx_stradd(&request, " (");
//     while(tmp) {
//         mx_stradd(&request, tmp->name);
//         mx_stradd(&request, " ");
//         mx_stradd(&request, tmp->type);
//         mx_stradd(&request, " ");
//         mx_stradd(&request, tmp->params);
//         if (tmp->next)
//             mx_stradd(&request, ", ");
//         tmp = tmp->next;
//     }
//     mx_stradd(&request, ");");
//     return request;    
// }

// void mx_create_table(const t_database t_db) {
//     char *err_msg = 0;
//     sqlite3 *db = NULL;
//     char *request = mx_get_requst_create_table(t_db);
//     int res = sqlite3_open(t_db.name_db, &db);

//     if (res!= SQLITE_OK)
//         mx_print_error("Cannot open database", 1, true);
//     else
//         res = sqlite3_exec(db, request, 0, 0, &err_msg);
//     if (res != SQLITE_OK) {
//         mx_print_error("Error create table", 1, true);
//         sqlite3_free(err_msg);
//         sqlite3_close(db);
//         return;
//     }
//     sqlite3_close(db);
//     mx_strdel(&request);
// }

// t_table *mx_create_t_table(char *name, char *params, char *type) {
//     t_table *table = (t_table*)malloc(sizeof(t_table));

//     table->name = mx_strdup(name);
//     table->params = mx_strdup(params);
//     table->type = mx_strdup(type);
//     table->next = NULL;
//     table->data = NULL;
//     return table;
// }

// void mx_push_t_table(t_table **table, char *name, char *params, char *type) {
//     t_table *tmp = *table;

//     if (!tmp) 
//         *table = mx_create_t_table(name, params, type);
//     else {
//         while (tmp->next)
//             tmp = tmp->next;
//         tmp->next = mx_create_t_table(name, params, type);
//     }
// }

// void mx_push_data_table(t_table **table, char **datas) {
//     t_table *tmp = *table;
//     int i = 0;

//     while(tmp) {
//         mx_strdel(&tmp->data);
//         tmp->data = mx_strdup(datas[i]);
//         tmp = tmp->next;
//         i++;
//     }
// }

// void mx_free_t_table(t_table **table) {
//     t_table *tmp = *table;
//     t_table *last = NULL;

//     while(tmp) {
//         last = tmp;
//         tmp = tmp->next;
//         mx_strdel(&last->name);
//         mx_strdel(&last->type);
//         mx_strdel(&last->params);
//         free(last);
//         last = NULL;
//     }
// }

// static char *mx_get_request_insert(const t_database t_db) {
//     char *request = mx_strjoin("INSERT INTO ", t_db.name_table);
//     t_table *tmp = t_db.table;

//     mx_stradd(&request, " (");
//     while(tmp) {
//         mx_stradd(&request, tmp->name);
//         if (tmp->next)
//             mx_stradd(&request, ", ");
//         tmp = tmp->next;
//     }
//     mx_stradd(&request, ") VALUES (");
//     tmp = t_db.table;
//     while(tmp) {
//         if (!mx_strcmp("TEXT", tmp->type))
//             mx_stradd(&request, "\'");
//         mx_stradd(&request, tmp->data);
//         if (!mx_strcmp("TEXT", tmp->type))
//             mx_stradd(&request, "\'");
//         if (tmp->next)
//             mx_stradd(&request, ", ");
//         tmp = tmp->next;
//     }
//     mx_stradd(&request, ");");
//     return request; 
// }

// void mx_insert_data(const t_database t_db) {
//     char *err_msg = 0;
//     char *request = mx_get_request_insert(t_db);
//     sqlite3 *db = NULL;
//     int res = sqlite3_open(t_db.name_db, &db);

//     if (res!= SQLITE_OK) 
//         mx_print_error("Cannot open database", 1, true);
//     else
//         res = sqlite3_exec(db, request, 0, 0, &err_msg);
//     if (res != SQLITE_OK) {
//         sqlite3_free(err_msg);
//         sqlite3_close(db);
//         mx_print_error("Error insert data", 2, true);
//     }
//     sqlite3_close(db);  
//     mx_strdel(&request); 
// }

// static char *mx_get_request_select(char *n_t, t_table *table, char *cond) {
//     char *request = NULL;
//     t_table *tmp = table;

//     mx_stradd(&request, "SELECT ");
//     if (!tmp)
//         mx_stradd(&request, "*");
//     else
//         while(tmp) {
//             mx_stradd(&request, tmp->name);
//             if (tmp->next)
//                 mx_stradd(&request, ",");
//             mx_stradd(&request, " ");
//             tmp = tmp->next;
//     }
//     mx_stradd(&request, " FROM ");
//     mx_stradd(&request, n_t);
//     mx_stradd(&request, " ");
//     mx_stradd(&request, cond);
//     mx_stradd(&request, ";");
//     return request;
// }

// static void mx_get_s_r(sqlite3_stmt *res, int col, t_list_arr **r) {
//     int step = 0;
//     char *buf = NULL;
//     char **tmp = NULL;

//     while(1) {
//         step = sqlite3_step(res);
//         if(step == SQLITE_ROW) {
//             tmp = mx_create_char_arr(col);
//             for (int i = 0; i < col; i++) {
//                 sqlite3_column_bytes(res, i);
//                 buf = (char*)sqlite3_column_text(res, i);
//                 tmp[i] = mx_strdup(buf);
//                 buf = NULL;
//             }
//             mx_arr_push_back(r, tmp);
//             mx_del_strarr(&tmp);
//         }
//         else if (step == SQLITE_DONE)
//             break;
//     }
// }

// static int mx_check_open_database(sqlite3 **db, t_database t_db) {
//     int res = sqlite3_open(t_db.name_db, db);

//     return res;
// }

// t_list_arr *mx_select_table(const t_database t_db, char *cond, int columns) {
//     sqlite3 *db = NULL;
//     char *request = mx_get_request_select(t_db.name_table, t_db.table, cond);
//     sqlite3_stmt *resp = NULL;
//     t_list_arr *response = NULL;

//     if (mx_check_open_database(&db, t_db) != SQLITE_OK)
//         mx_print_error("Cannot open database", 1, true);
//     else {
//         sqlite3_prepare_v2(db, request, mx_strlen(request) + 1, &resp, NULL);
//         sqlite3_close(db);
//         mx_get_s_r(resp, columns, &response);
//         return response; 
//     }
//     mx_strdel(&request);
//     return NULL;
// }

// void mx_print_list_arr(t_list_arr *list) {
//     t_list_arr *tmp = list;

//     while(tmp) {
//         mx_print_strarr(tmp->data, " | ");
//         if (tmp->next)
//             mx_printchar('\n');
//         tmp = tmp->next;
//     }
// }

// static void mx_get_request_update2(char **request, char *condition) {
//     mx_stradd(request, " ");
//     mx_stradd(request, condition);
//     mx_stradd(request, ";");   
// }

// static char *mx_get_request_update(t_database t_db, char *condition) {
//     char *request = mx_strdup("UPDATE ");
//     t_table *tmp = t_db.table;

//     mx_stradd(&request, t_db.name_table);
//     mx_stradd(&request, " SET");
//     while(tmp) {
//         mx_stradd(&request, " ");
//         mx_stradd(&request, tmp->name);
//         mx_stradd(&request, " = ");
//         if (!mx_strcmp("TEXT", tmp->type))
//             mx_stradd(&request, "\'");
//         mx_stradd(&request, tmp->data);
//         if (!mx_strcmp("TEXT", tmp->type))
//             mx_stradd(&request, "\'");
//         if (tmp->next)
//             mx_stradd(&request, ",");
//         tmp = tmp->next;
//     }
//     mx_get_request_update2(&request, condition);
//     return request;
// }

// void mx_update_data(t_database t_db, char *condition) {
//     char *request = mx_get_request_update(t_db, condition);
//     char *err_msg = 0;
//     sqlite3 *db = NULL;
//     int res = sqlite3_open(t_db.name_db, &db);

//     if (res!= SQLITE_OK) 
//         mx_print_error("Cannot open database", 1, true);
//     else
//         res = sqlite3_exec(db, request, 0, 0, &err_msg);
//     if (res != SQLITE_OK) {
//         sqlite3_free(err_msg);
//         sqlite3_close(db);
//         mx_print_error("Error update data", 2, true);
//     }
//     sqlite3_close(db);  
//     mx_strdel(&request); 
// }

// t_table *mx_copy_struct_t_table(t_table *table) {
//     t_table *copy = NULL;
//     t_table *tmp = table;
    
//     if(!tmp)
//         return NULL;
//     while(tmp) {
//         mx_push_t_table(&copy, tmp->name, tmp->params, tmp->type);
//         tmp = tmp->next;
//     }
//     return copy;
// }

// static char *mx_get_request_delete(t_database t_db, char *condition) {
//     char *request = mx_strdup("DELETE FROM ");

//     mx_stradd(&request, t_db.name_table);
//     mx_stradd(&request, " ");
//     mx_stradd(&request, condition);
//     mx_stradd(&request, ";");
//     return request;
// }

// void mx_delete_data(t_database t_db, char *condition) {
//     char *request = mx_get_request_delete(t_db, condition);
//     char *err_msg = 0;
//     sqlite3 *db = NULL;
//     int res = sqlite3_open(t_db.name_db, &db); 

//     if (res!= SQLITE_OK) 
//         mx_print_error("Cannot open database", 1, true);
//     else
//         res = sqlite3_exec(db, request, 0, 0, &err_msg);
//     if (res != SQLITE_OK) {
//         sqlite3_free(err_msg);
//         sqlite3_close(db);
//         mx_print_error("Error delete data", 2, true);
//     }
//     sqlite3_close(db);
//     mx_strdel(&request);
// }

int main (int argc, char *argv[]) {
    sqlite3 *db = NULL;
    t_table *column = NULL;
    t_list_arr *res = NULL;
    t_database t_db;
    t_table *table1 = NULL;
    t_db.name_db = argv[1];
    t_db.name_table = argv[2];

    if (argc != 3)
        mx_print_error("Usage &database &table", 1, true);

    char *datas[3] = {"NULL", "ldobrovols", "123"};
    char *datas2[1] = {"leo"};
    mx_push_t_table(&column, "id", "PRIMARY KEY", "INTEGER"); //каждая стуктура - это колонка в таблице
    mx_push_t_table(&column, "login", NULL, "TEXT"); //добавляем еще одну колонку
    mx_push_t_table(&column, "passwd", NULL, "TEXT");
    t_db.table = column;
    mx_create_db(argv[1]); //созадем базу
    mx_create_table(t_db); // создаем таблицу
    mx_push_data_table(&column, datas); //добавляем в структуру колонок реквизит с данными по каждой колонке
    t_db.table = column;
    mx_insert_data(t_db);  //добавляем в таблицу данные
    //mx_insert_data(t_db);
    mx_push_t_table(&table1, "login", NULL, "TEXT");
    mx_push_data_table(&table1, datas2);
    t_db.table = table1;
    mx_update_data(t_db, "WHERE id = 1");
    t_db.table = column;
    res = mx_select_table(t_db, NULL, 3); //пятым параметром указываем условие Например "WHERE ID=1", шестой параметр - количество столбцов в таблице В данной таблице и две - id, login
    mx_print_list_arr(res);
    //mx_delete_data(t_db, "WHERE login = 'leo'");
    res = mx_select_table(t_db, NULL, 3);
    mx_print_list_arr(res);
    mx_free_t_table(&column);
    mx_free_arr_list(&res);
    //system("leaks -q a.out");
}
