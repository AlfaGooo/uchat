#include "libmx.h"
#include "sqlite3.h"



//database
typedef struct s_table {
    char *name;
    char *params;
    char *type;
    char *data;
    struct s_table *next;
} t_table;

typedef struct s_database {
    char *name_db;
    char *name_table;
    t_table *table;
} t_database;

//database
void mx_create_db(char const *name_db);
void mx_create_table(const t_database t_db);
t_table *mx_create_t_table(char *name, char *params, char *type);
void mx_push_t_table(t_table **table, char *name, char *params, char *type);
void mx_push_data_table(t_table **table, char **datas);
void mx_free_t_table(t_table **table);
void mx_insert_data(const t_database t_db);
t_list_arr *mx_select_table(const t_database t_db, char *cond, int columns);
void mx_update_data(t_database t_db, char *condition);
t_table *mx_copy_struct_t_table(t_table *table);
void mx_delete_data(t_database t_db, char *condition);

