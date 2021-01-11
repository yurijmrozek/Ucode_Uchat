#include "server.h"

void *mx_accept_user(void *data) {
    t_server *server = (t_server *)data;
    struct sockaddr_in PeerAddr;
    socklen_t PeerAddrLen = sizeof(PeerAddr);
    int socket1 = accept(server->socket0, (struct sockaddr*)
                         &PeerAddr, &PeerAddrLen);

    server->flag--;
    if (socket1 < 0) {
        perror("Cannot accept"); exit(1);
    }
    // A connection is accepted. The new socket "s1" is created
    // for data input/output. The peeraddr structure is filled in with
    // the address of connected entity, print it.
    printf(
        "Connection from IP %d.%d.%d.%d, port %d\n",
        (ntohl(PeerAddr.sin_addr.s_addr) >> 24) & 0xff, // High byte of address
        (ntohl(PeerAddr.sin_addr.s_addr) >> 16) & 0xff, // . . .
        (ntohl(PeerAddr.sin_addr.s_addr) >> 8) & 0xff,  // . . .
        ntohl(PeerAddr.sin_addr.s_addr) & 0xff,         // Low byte of addr
        ntohs(PeerAddr.sin_port)
    );
    mx_recv_client(server, socket1);
    return NULL;
}
