#include "server.h"

int mx_get_socket_id(sqlite3 *db, int id) {
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(db, "SELECT SOCKET FROM users "  \
                                "WHERE ID = ?1",
                            -1, 0, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, id);
    sqlite3_step(stmt);
    int sockfd = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    return sockfd;
}
