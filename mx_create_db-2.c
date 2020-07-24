#include <sqlite3.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "libmx.h"



typedef struct s_sql_resp {
    char **data;
    struct s_sql_resp *next;
} t_sql_resp;

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

static void mx_create_db(char const *name_db) {
    int fd = open(name_db, O_WRONLY | O_CREAT | O_TRUNC, 0600);

    if (fd) {
        printf("Database %s is create!\n", name_db);
    }
    else
        printf("ERROR FD\n");
    close(fd);
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

void mx_push_data_table(t_table **table, char **datas) {
    t_table *tmp = *table;
    int i = 0;

    while(tmp) {
        mx_strdel(&tmp->data);
        tmp->data = datas[i];
        tmp = tmp->next;
        i++;
    }

}

void mx_insert_data(char const *name_db, char const *name_table, sqlite3 **db, t_table *table) {
    int res = sqlite3_open(name_db, db);
    char *err_msg = 0;

    t_table *tmp = table;
    char *request = mx_strjoin("INSERT INTO ", name_table);

    mx_stradd(&request, " (");
    while(tmp) {
        mx_stradd(&request, tmp->name);
        if (tmp->next)
            mx_stradd(&request, ", ");
        tmp = tmp->next;
    }
    mx_stradd(&request, ") VALUES (");
    tmp = table;
    while(tmp) {
        if (!mx_strcmp("TEXT", tmp->type))
            mx_stradd(&request, "\'");
        mx_stradd(&request, tmp->data);
        if (!mx_strcmp("TEXT", tmp->type))
            mx_stradd(&request, "\'");
        if (tmp->next)
            mx_stradd(&request, ", ");
        tmp = tmp->next;
    }
    mx_stradd(&request, ");");
    mx_printstr(request);
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

int mx_strarr_len(char **arr) {
    int len = 0;

    while(arr[len])
        len++;
    return len;
}

t_sql_resp *mx_create_sql_resp(char **data) {
    t_sql_resp *tmp = (t_sql_resp*)malloc(sizeof(t_sql_resp));
    int len = mx_strarr_len(data);
    
    tmp->data = mx_create_char_arr(len);
    for (int i = 0; data[i]; i++)
        tmp->data[i] = mx_strdup(data[i]);
    tmp->next = NULL;
    return tmp;
}

void mx_push_sql_resp(t_sql_resp **resp, char **data) {
    t_sql_resp *tmp = *resp;

    if(!tmp)
        *resp = mx_create_sql_resp(data);
    else {
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = mx_create_sql_resp(data);
    }
}

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



int main (int argc, char *argv[]) {
    sqlite3 *db = NULL;
    t_table *column = NULL;
    t_sql_resp *res = NULL;

    if (argc != 3)
        mx_print_error("Usage &database &table", 1, true);

    char *datas[4] = {"NULL", "dfgfdg", "0000", "00000000f@lkj.com"};


    mx_push_t_table(&column, mx_strdup("id"), mx_strdup("PRIMARY KEY"), mx_strdup("INTEGER")); //каждая стуктура - это колонка в таблице
    mx_push_t_table(&column, mx_strdup("login"), NULL, mx_strdup("TEXT")); //добавляем еще одну колонку
    mx_push_t_table(&column, mx_strdup("password"), NULL, mx_strdup("TEXT"));
    mx_push_t_table(&column, mx_strdup("email"), NULL, mx_strdup("TEXT"));
    //mx_create_db(argv[1]); //созадем базу
    //mx_create_table(argv[1], argv[2], &db, column); // создаем таблицу
    mx_push_data_table(&column, datas); //добавляем в структуру колонок реквизит с данными по каждой колонке
    mx_insert_data(argv[1], argv[2], &db, column);  //добавляем в таблицу данные
    res = mx_select_table(argv[1], argv[2], &db, column, NULL, 2); //пятым параметром указываем условие Например "WHERE ID=1", шестой параметр - количество столбцов в таблице В данной таблице и две - id, login
    mx_print_sql_resp(res);
}
