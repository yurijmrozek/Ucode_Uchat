#include "server.h"

void mx_recv_client(t_server *server, int socket1) {
    char Buffer[1024];
    int result;

    while(1) {
        result = read(socket1, Buffer, 1023);
        Buffer[result] = '\0';
        
        if (result > 0) {
            if (cJSON_Parse(Buffer))
                mx_json_manager(Buffer, server, socket1);
            printf("\n\nReceived %d bytes:\n\n%s\n\n", result, Buffer);
        }
        else {
            mx_clean_socket_db(server->t_db, socket1);
            close(socket1);
            break;
        }
        bzero(Buffer, 1024);
    }
}
