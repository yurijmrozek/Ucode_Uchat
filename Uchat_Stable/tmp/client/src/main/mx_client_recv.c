#include "client.h"

static void disconnect_user(int sockfd) {
    close(sockfd);
    gtk_main_quit();
}

void *mx_client_recv(void *data) {
    t_chat *chat = (t_chat *)data;
    int result;
    char recvBuff[1024];
    
    while (1) {
        result = read(chat->sockfd, recvBuff, 1023);
        recvBuff[result] = '\0';
        if (result > 0) {
            mx_cjson_parser(recvBuff, chat);
            printf("\n\nReceived %d bytes:\n\n%s\n\n", result, recvBuff);
        }
        else {
            perror("Read error");
            disconnect_user(chat->sockfd);
            break;
        }
        bzero(recvBuff, 1024);
    }
    return data;
}
