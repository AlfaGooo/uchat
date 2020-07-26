#include "libmx.h"
#include "cJSON.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>


#define BUFFER_SIZE 1025
#define WINDOW_MAIN_WEIGHT 1000
#define WINDOW_MAIN_HEIGHT 700

typedef struct s_client_main {
    char *login;
    char *name;
    char *surname;
    char *rooms;
    GtkApplication *win;
    GtkWidget *but;
} t_client_main;
