#include "client.h"

static void disconnect_user(int sockfd) {
    close(sockfd);
    gtk_main_quit();
}

void *mx_client_recv(void *data) {
    t_chat *chat = data;
    int result;
    char recvBuff[1024];
    
    while (1) {
        result = read(chat->sockfd, recvBuff, 1023);
        if (result > 0) {
            if (cJSON_Parse(recvBuff))
                mx_cjson_parser(recvBuff, chat);
        }
        else {
            perror("Read error");
            disconnect_user(chat->sockfd);
            break;
        }
        printf("\n\nReceived %d bytes:\n\n%s\n\n", result, recvBuff);
    }
    return data;
}
