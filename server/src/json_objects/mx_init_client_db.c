#include "server.h"

void mx_init_client_db(sqlite3 *db, int connfd) {
    mx_send_cntc(db, connfd);
}
