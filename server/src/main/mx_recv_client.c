#include "server.h"

static void disconnect_user(int socket1) {
    write(socket1, "Disconnect\r\n", 12);
    close(socket1);
}

void mx_recv_client(t_server *server, int socket1) {
    char Buffer[1024];
    int result;

    while(1) {
        result = read(socket1, Buffer, 1023);

        if (result > 0) {
            if (cJSON_Parse(Buffer))
                mx_json_manager(Buffer, server, socket1);
            printf("\n\nReceived %d bytes:\n\n%s\n\n", result, Buffer);
        }
        else {
            mx_clean_socket_db(server->t_db, socket1);
            disconnect_user(socket1);
            break;
        }
        bzero(Buffer, 1024);
    }
    write(socket1, "Disconnect\r\n", 12);
    close(socket1);  // Close the data socket
}
