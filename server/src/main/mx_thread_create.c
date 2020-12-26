#include "server.h"

int mx_thread_create(t_server *server) {
    pthread_t ThreadM[100];
    int i = 0;
    int Mastr;
    
    while(i < 100) {
        if(server->flag < 1) {
            Mastr = pthread_create(&(ThreadM[i]), NULL, 
                                   &mx_accept_user, server);
            if (Mastr != 0) {
                printf("Cannot create thread %d",i+1); exit(1);
            }
            printf("Thread %d is created.\n", i + 1);
            i++;
            server->flag++; 
        }
    }
    while(i > -1) {
        pthread_join(ThreadM[i], NULL);
        i--;
    }
    server->result = close(server->socket0);    // Close the listen socket
    return 0;
}
