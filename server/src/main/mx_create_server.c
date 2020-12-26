#include "server.h"

int mx_create_server(t_server *server) {
    server->socket0 = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket0 < 0) {
        perror("Cannot create a socket"); 
        exit(1);
    }
    // Fill in the address structure containing self address
    struct sockaddr_in MyAddr;
    memset(&MyAddr, 0, sizeof(struct sockaddr_in));
    MyAddr.sin_family = AF_INET;
    MyAddr.sin_port = htons(server->port);        // Port to listen
    MyAddr.sin_addr.s_addr = htonl(INADDR_ANY); 

    // Bind a socket to the address
    int Result = bind(server->socket0, (struct sockaddr*) &MyAddr, sizeof(MyAddr));
    if (Result < 0) {
        perror("Cannot bind a socket"); exit(1);
    }

    // Set the "LINGER" timeout to zero, to close the listen socket
    // immediately at program termination.
    struct linger LingerOpt = { 1, 0 }; // Linger active, timeout 0
    setsockopt(server->socket0, SOL_SOCKET, SO_LINGER,
               &LingerOpt, sizeof(LingerOpt));

    // Now, listen for a connection
    Result = listen(server->socket0, 100);    // "100" is the maximal length of the queue
    if (Result < 0) {
        perror("Cannot listen"); exit(1);
    }
    return 1;
}
