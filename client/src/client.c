#include "client.h"

// int main(int argc, char *argv[]) {
//     int sockfd = 0, n = 0;
//     char recvBuff[1024];
//     struct sockaddr_in serv_addr;

//     if(argc != 2) {
//         printf("\n Usage: %s <ip of server> \n",argv[0]);
//         return 1;
//     }
//     memset(recvBuff, '0',sizeof(recvBuff));
//     if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//     {
//         printf("\n Error : Could not create socket \n");
//         return 1;
//     }
//     memset(&serv_addr, '0', sizeof(serv_addr));
//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_port = htons(5000);
//     if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
//     {
//         printf("\n inet_pton error occured\n");
//         return 1;
//     }
//     if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
//     {
//        printf("\n Error : Connect Failed \n");
//        return 1;
//     }
//     while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
//     {
//         recvBuff[n] = 0;
//         if(fputs(recvBuff, stdout) == EOF)
//         {
//             printf("\n Error : Fputs error\n");
//         }
//         //break;
//     }
//     if(n < 0)
//     {
//         printf("\n Read error \n");
//     }
//     return 0;
// }


t_client *mx_create_client_struct(const char *IP) {
    t_client *client = (t_client*)malloc(sizeof(t_client));
    int in_st = 0;

    client->sockfd = 0;
    client->confd = 0;
    client->serv_addr.sin_family = AF_INET;
    client->serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
    client->serv_addr.sin_port = htons(SERVER_PORT); 
    in_st = inet_pton(AF_INET, IP, &client->serv_addr.sin_addr);
    if(in_st <= 0)
        mx_print_error("\n inet_pton error occured\n", 1, true);

    return client;
}

void mx_client_loop(t_client *client) {
    char buf[11];
    buf[10] = 0;
    int i = 48;
    int write_num = 0;
    
    mx_printint(client->confd);
    mx_printstr("\n");
    while(1) {
        mx_memset(&buf, i, 10);
        write_num = write(client->sockfd, &buf, 10);
        if (write_num > 0)
            break;
    }
}


int main (int argc, char *argv[]) {
    t_client *c = NULL;
    int confd = 0;
    
    if(argc != 2) {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }
    c = mx_create_client_struct(argv[1]);
    c->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (c->sockfd == -1)
        mx_print_error("\n error create socket\n", 1, true);
    c->confd = connect(c->sockfd, (struct sockaddr *)&c->serv_addr, sizeof(c->serv_addr));
    if (c->confd < 0)
        mx_print_error("\n error create socket\n", 1, true);
    mx_client_loop(c);
}