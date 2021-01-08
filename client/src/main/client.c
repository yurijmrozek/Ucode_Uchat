#include "client.h"

int main(int argc, char *argv[]) {
    t_chat *chat = (t_chat *)malloc(sizeof(t_chat));
    
    mx_valid_argv(argc, argv, chat);
    if (mx_create_conn(chat) == 1) {
        printf("Connection estabilished\n");
        mx_start_chat(chat);
    }
    close(chat->sockfd);
    free(chat);
    return 0;
}
