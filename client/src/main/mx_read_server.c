#include "client.h"

void *mx_read_server(void *arg) {
    client_t *cli = (client_t *)arg;
    int rlen = 0;

    while(read(cli->sockfd, &rlen, 4) > 0) {
        char buff_in[rlen + 1];
        bzero(buff_in, rlen + 1);
        read(cli->sockfd, buff_in, rlen);

        if (!strlen(buff_in))
            continue;

        /* Special options */
        gdk_threads_enter();
        mx_json_manager(buff_in, cli);
        gdk_threads_leave();
    }

    close(cli->sockfd);
    free(cli);
    gtk_main_quit();
    
    return NULL;
}
