#include "client.h"

int main(int argc, char *argv[]) {
    client_t *cli = (client_t *)malloc(sizeof(client_t));
    mx_valid_argv(argc, argv, cli);
    mx_create_connection(cli);
    return 0;
}
