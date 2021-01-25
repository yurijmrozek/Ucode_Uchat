#include "server.h"

int main(int argc, char *argv[]) {
    mx_daemon();
    if (argc != 2 || strlen(argv[1]) != 4 || !atoi(argv[1])) {
        printf("Usage: ./uchat_server [port]\n");
        exit(1);
    }
    mx_create_server(argv);
    exit(1);
}
