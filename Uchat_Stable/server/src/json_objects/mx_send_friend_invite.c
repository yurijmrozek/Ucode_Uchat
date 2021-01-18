#include "server.h"

void mx_send_friend_invite(sqlite3 *db, char *username) {
    int cid = mx_get_id_login(db, username);
    int sockfd = mx_get_socket_id(db, cid);

    mx_send_cntc(db, sockfd);
}
