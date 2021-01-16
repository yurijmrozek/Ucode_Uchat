#include "client.h"

void *mx_read_server(void *arg) {
    client_t *cli = (client_t *)arg;
    char buff_in[1024];
    int rlen;

    while((rlen = read(cli->sockfd, buff_in, sizeof(buff_in) - 1)) > 0) {
        buff_in[rlen] = '\0';
        
        if (!strlen(buff_in))
            continue;

        /* Special options */
        gdk_threads_enter();
        printf("\n\n<< Recieved %d bytes:\n\n%s\n\n<<", rlen, buff_in);
        mx_json_manager(buff_in, cli);
        gdk_threads_leave();
        bzero(buff_in, 1024);
    }

    close(cli->sockfd);
    free(cli);
    gtk_main_quit();
    
    return NULL;
}
