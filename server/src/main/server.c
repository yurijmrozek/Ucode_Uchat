#include "server.h"

int main(int argc, char *argv[]) {
    t_server *server = (t_server *)malloc(sizeof(t_server));
    server->argc = argc;
    server->argv = argv;
    server->flag = 0;

    mx_valid_argv(server);
    mx_create_server(server);
    printf("Server created\n");
    mx_thread_create(server);
}

