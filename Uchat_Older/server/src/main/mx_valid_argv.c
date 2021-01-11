#include "server.h"

int mx_valid_argv(t_server *server) {
    bool valid = true;

    if (server->argc == 2) {
        if (server->argc != 2 || strlen(server->argv[1]) != 4)
            valid = false;
        for (int i = 0; server->argv[1][i]; i++)
            if (!isdigit(server->argv[1][i]))
                valid = false;
        if (!valid) {
            write(2, "usage: ./uchat_server [port]\n", 30);
            exit(2);
        }
    }
    else {
        write(2, "usage: ./uchat_server [port]\n", 30);
        exit(2);
    }
    server->port = atoi(server->argv[1]);
    return 1;
}
