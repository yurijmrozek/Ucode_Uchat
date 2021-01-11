#include "client.h"

int mx_create_conn(t_chat *chat) {
    struct sockaddr_in serv_addr;

    chat->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(chat->con_port);
    inet_pton(AF_INET, chat->con_ip, &serv_addr.sin_addr);
    if (connect(chat->sockfd, (struct sockaddr *)&serv_addr,
        sizeof(serv_addr)) < 0) {
        printf("\nError : Connect Failed \n");
        return 2;
    }
    return 1;
}
