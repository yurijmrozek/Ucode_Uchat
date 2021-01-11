#include "client.h"

void mx_create_connection(client_t *cli) {
    struct sockaddr_in address;
    int len;

    cli->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cli->sockfd < 0) {
        perror("socket");
        exit(2);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(cli->con_ip);
    address.sin_port = htons(cli->con_port);
    len = sizeof(address);

    int result = connect(cli->sockfd, (struct sockaddr *)&address, len);
    if (result < 0) {
        perror("Connection error ");
        exit(2);
    }

    gdk_threads_init();
    gtk_init(NULL, NULL);
    mx_init_authoriz_gui(cli);
    g_thread_new("mx_read_server", mx_read_server, (void *)cli);
    gtk_main();
    gdk_threads_leave();
}
