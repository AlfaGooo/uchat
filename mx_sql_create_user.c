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

//первый параметр инсерт

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

// void mx_insert_data(char const *name_db, char const *name_table, sqlite3 **db, t_table *table);
// mx_insert_data(argv[1], argv[2], &db, column);  //добавляем в таблицу данные
// mx_create_table(DATABASE_NAME, "users", &db, column_u);

// void mx_push_t_table(t_table **table, char *name, char *params, char *type) {

//     mx_push_t_table(&column_u, "login", NULL, "TEXT");
//     mx_push_t_table(&column_u, "passw", NULL, "TEXT");
//     mx_push_t_table(&column_u, "email", NULL, "TEXT");

// //static void get_data_table()
// bool mx_sql_create_user(t_user *login, t_user *password, t_user *email) {
// // bool mx_sql_create_user(t_table *login, t_table *password, t_table *email) {
//     sqlite3 *db = NULL;
//     t_table *column_log = NULL;
//     t_table *column_pas = NULL;
//     t_table *column_em = NULL;

//     char *log[2] = {"users", "login"}; //null == table
//     mx_push_data_table(&column_log, log); //добавляем в структуру колонок реквизит с данными по каждой колонке
//     mx_insert_data(DATABASE_NAME, "users", &db, column_log);

//     char *pass[2] = {"users", "password"};
//     mx_push_data_table(&column_pas, pass);
//     mx_insert_data(DATABASE_NAME, "users", &db, column_pas);

//     char *em[2] = {"users", "email"};
//     mx_push_data_table(&column_em, em);
//     mx_insert_data(DATABASE_NAME, "users", &db, column_em);

//     return true;

// }


typedef struct s_user {
    char *login;
    char *password;
    char *email;
    struct s_user *next;
} t_user;

// void mx_push_data_table(t_table **table, char **datas) {
//     t_table *tmp = *table;
//     int i = 0;

//     while(tmp) {
//         mx_strdel(&tmp->data);
//         tmp->data = datas[i];
//         tmp = tmp->next;
//         i++;
//     }

// }

bool mx_sql_create_user(char *login, char *password, char *email) {
    sqlite3 *db = NULL;
    t_table *column = NULL;

    char *log[3] = {"NULL", login, password, email};

    //mx_push_t_table(&column, "id", "PRIMARY KEY", "INTEGER");
    mx_push_t_table(&column, "login", NULL, "TEXT"); //добавляем еще одну колонку
    mx_push_t_table(&column, "password", NULL, "TEXT");
    mx_push_t_table(&column, "email", NULL, "TEXT");

    mx_push_data_table(&column, log); //добавляем в структуру колонок реквизит с данными по каждой колонке
    mx_insert_data(DATABASE_NAME, "users", &db, column);

    mx_push_data_table(&column, log);
    mx_insert_data(DATABASE_NAME, "users", &db, column);

    mx_push_data_table(&column, log);
    mx_insert_data(DATABASE_NAME, "users", &db, column);

    //free

    return true;
    //в каком случае фолс?

}
