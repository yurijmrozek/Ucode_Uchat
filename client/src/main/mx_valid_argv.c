#include "client.h"

static void err() {
    write(2,
          "Chat.\n"
          "Usage:\n"
          "         client [IP_addResults_of_server [port_of_server]]\n"
          "     where IP_address_of_server is either IP number of server\n"
          "     or a symbolic Internet name, default is \"localhost\";\n"
          "     port_of_server is a port number.\n"
          "The client connects to a server which address is given in a\n"
          "command line, receives a message from a server, sends the message\n",
          357);
    exit(2);
}

static char *check_port(char **argv) {
    int i = -1;
    bool valid = true;
    if (strlen(argv[2]) != 4)
        valid = false;
    while (argv[2][++i])
        if (!isdigit(argv[2][i])) {
            valid = false;
            break;
        }
    if (!valid)
        err();
    return argv[2];
}

static char *check_ip(char **argv) {
    int dots = 0;
    bool valid = true;
    for (int i = 0; argv[1][i]; i++) {
        if (argv[1][i] == '.')
            dots++;
        if (argv[1][i] != '.' && !isdigit(argv[1][i]))
            valid = false;
        if ((argv[1][i] == '.' && argv[1][i + 1] == '.')
            || (argv[1][i] == '.' && !isdigit(argv[1][i + 1]))
            || (argv[1][i] == '.' && !isdigit(argv[1][i - 1])))
            valid = false;
    }
    if (dots != 3 || valid == false)
        err();
    return argv[1];
}

void mx_valid_argv(int argc, char **argv, client_t *cli) {
    if (argc != 3)
        err();
    cli->con_ip = check_ip(argv);
    cli->con_port = atoi(check_port(argv));
}
