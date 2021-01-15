#include "server.h"

int mx_logout_event_db(int connfd, sqlite3 *db) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;
    rv = sqlite3_prepare_v2(db,       "UPDATE users "       \
                                      "SET SOCKET = ?1"     \
                                      "WHERE SOCKET = ?2",///
                            -1, &stmt, 0);///////////////////
    sqlite3_bind_int(stmt, 1, -1);
    sqlite3_bind_int(stmt, 2, connfd);
    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return 1;
    }
    sqlite3_finalize(stmt);
    return 2;
}
