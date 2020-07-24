//forun for all users


bool mx_sql_add_user_to_room(int room_id, int user_id) {
    sqlite3 *db = NULL;
    t_table *column = NULL;
    t_sql_resp *res_u = NULL;
    t_sql_resp *res_r = NULL;

    if (mx_sql_create_user());

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

void mx_create_forum(int room_id, int user_id)
    sqlite3 *db = NULL;
    t_table *column = NULL;
    t_sql_resp *res_u = NULL;
    t_sql_resp *res_r = NULL;

    
}