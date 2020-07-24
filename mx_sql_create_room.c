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

room (id INTEGER PRIMARY KEY, name TEXT );

mx_push_t_table(&column_r, "id", "PRIMARY KEY", "INTEGER"); //table room
mx_push_t_table(&column_r, "name", NULL, "TEXT"); // название комнаты

bool mx_sql_create_room(char *login, char *password, char *email) {
    sqlite3 *db = NULL;
    t_table *column = NULL;

    char *log[3] = {"NULL", login, password, email};

    mx_push_t_table(&column, "id", "PRIMARY KEY", "INTEGER");
    mx_push_t_table(&column, "name", NULL, "TEXT"); //добавляем еще одну колонку

    // mx_push_data_table(&column, log); //добавляем в структуру колонок реквизит с данными по каждой колонке
    // mx_insert_data(DATABASE_NAME, "users", &db, column);

    // mx_push_data_table(&column, log);
    // mx_insert_data(DATABASE_NAME, "users", &db, column);

    // mx_push_data_table(&column, log);
    // mx_insert_data(DATABASE_NAME, "users", &db, column);

    //free

    return true;
    //в каком случае фолс?

}

if user enter to room сравнить пароль логин и емейл если есть то захожу
потом заполняем таблицу логином

