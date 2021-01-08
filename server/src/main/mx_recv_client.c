#include "server.h"

void mx_recv_client(t_server *server, int socket1) {
    char Buffer[2048];
    int result;

    while(1) {
        result = read(socket1, Buffer, 2047);
        Buffer[result] = '\0';
        
        if (result > 0) {
            mx_json_manager(Buffer, server, socket1);
            printf("\n\nReceived %d bytes:\n\n%s\n\n", result, Buffer);
        }
        else {
            mx_clean_socket_db(server->t_db, socket1);
            close(socket1);
            break;
        }
        bzero(Buffer, 2048);
    }
}
