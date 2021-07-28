#include "server.h"

void *mx_handle_client(void *arg) {
    pthread_mutex_t topic_mutex = PTHREAD_MUTEX_INITIALIZER;
    char buff_out[BUFFER_SZ];
    char buff_in[BUFFER_SZ / 2];
    int rlen;

    cli_count++;
    client_t *cli = (client_t *)arg;

    printf("<< accept ");
    print_client_addr(cli->addr);
    printf(" referenced by %d\n", cli->uid);
    
    /* Receive input from client */

    while ((rlen = read(cli->connfd, buff_in, sizeof(buff_in) - 1)) > 0) {
        buff_in[rlen] = '\0';
        buff_out[0] = '\0';

        /* Ignore empty buffer */
        if (!strlen(buff_in))
            continue;

        /* Special options */
        pthread_mutex_lock(&topic_mutex);
        mx_json_manager(buff_in, cli->connfd, cli);
        pthread_mutex_unlock(&topic_mutex);
    }

    /* Close connection */
    mx_logout_event_db(cli->connfd, cli->db);
    close(cli->connfd);

    /* Delete client from queue and yield thread */
    queue_delete(cli->uid);
    printf("<< quit ");
    print_client_addr(cli->addr);
    printf(" referenced by %d\n", cli->uid);
    free(cli);
    cli_count--;
    pthread_detach(pthread_self());

    return NULL;
}
