#include "server.h"

// int main() {
//     int listenfd = 0, connfd = 0;
//     struct sockaddr_in serv_addr;
//     char recvBuff[1024];
//     char sendBuff[1025];
//     time_t ticks;
//     int n = 0;

//     listenfd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET - ipv4, SOCK_STREAM - TCP protocol
//     memset(&serv_addr, '0', sizeof(serv_addr));
//     memset(sendBuff, '0', sizeof(sendBuff));

//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//     serv_addr.sin_port = htons(5000);

//     bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
//     listen(listenfd, 10);

//     while(1) {
//         connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
//         ticks = time(NULL);
//         snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
//         write(connfd, sendBuff, strlen(sendBuff));
//         while ( (n = read(connfd, recvBuff, sizeof(recvBuff)-1)) > 0)
//         {
//             recvBuff[n] = 0;
//             if(fputs(recvBuff, stdout) == EOF)
//             {
//                 printf("\n Error : Fputs error\n");
//             }
//         }             
//         close(connfd);
//         sleep(1);
//     }
// }



void *mx_server_client_init(void *connfd) {
    int client_fd = *(int*) connfd;
    unsigned long fd = (unsigned long) client_fd;
    char buf[SOCKET_BUFFER_SIZE];
    int read_num = 0;

    mx_memset(&buf, client_fd, 20);
    mx_memset(&buf[20], 0, SOCKET_BUFFER_SIZE - 20);
    mx_printint(client_fd);
    while(1) {
        read_num = read(client_fd, &buf, 20);
        if (read_num > 0)
            break;
    }
    mx_printstr(buf);
    pthread_exit(0);
}

t_server *mx_create_server_struct() {
    t_server *server = (t_server*)malloc(sizeof(t_server));

    server->server_fd = 0;
    server->send_buff = mx_strnew(SEND_BUFF_SIZE);
    server->serv_addr.sin_family = AF_INET;
    server->serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server->serv_addr.sin_port = htons(SERVER_PORT);
    return server;
}


void mx_server_loop(t_server *serv) {
    int connfd = 0;
    pthread_t treat[MAX_CLIENTS];
    int client_index = 0;

    while(1) {
        connfd = accept(serv->server_fd, (struct sockaddr*)NULL, NULL);
        pthread_create(&treat[client_index], NULL, mx_server_client_init, &connfd);
        client_index++;
    }
}


int main () {
    t_server *s = mx_create_server_struct();
    
    s->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (s->server_fd == -1)
        exit(1);
    bind(s->server_fd, (struct sockaddr*)&s->serv_addr, sizeof(s->serv_addr));
    listen(s->server_fd, MAX_CLIENTS);
    mx_server_loop(s);
    close(s->server_fd);
}
