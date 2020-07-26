#include "libmx.h"
#include "cJSON.h"
#include <time.h>

#define CONNECT "0"
#define CONNECT_REQUEST_FILE "mx_connect_request.json"
#define CONNECT_RESPONSE_FILE "mx_connect_response.json"




char *mx_get_current_time() {
    int times = time(NULL);

    return mx_itoa(times);
}

char *mx_connect_request_to_json() {
    char *tmp = mx_file_to_str(CONNECT_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times); 
    mx_strdel(&times);
    return tmp;
}

char *mx_connect_response_to_json(int status) {
    char *tmp = mx_file_to_str(CONNECT_RESPONSE_FILE);
    char *times = mx_get_current_time();
    char *st = mx_itoa(status);

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&status", st); 
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;   
}

int main(int argc, char *argv[]) {
    //char *res = mx_connect_request_to_json();
    char *res = mx_connect_response_to_json(1);

    cJSON *root = NULL;

    
    mx_printstr(res);
    //mx_strdel(&res);
    root = cJSON_Parse(res);
    if (print_preallocated(root) != 0) {
        cJSON_Delete(root);
        exit(EXIT_FAILURE);
    }
    cJSON_Delete(root);
    system("leaks -q a.out");
}
