#include "server.h"

int main(int argc, char *argv[]) {
    t_server *server = (t_server *)malloc(sizeof(t_server));
    server->t_db = (t_database *)malloc(sizeof(t_database));

    server->argc = argc;
    server->argv = argv;
    server->flag = 0;

    mx_valid_argv(server);
    mx_create_server(server);
    // mx_daemon();
    mx_oc_db(server->t_db);
    printf("Server created\n");
    mx_accept_user(server);
    free(server->t_db);
    free(server);
}
