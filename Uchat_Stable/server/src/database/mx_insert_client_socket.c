#include "server.h"

void mx_insert_client_socket(sqlite3 *db, char *username, int connfd) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "UPDATE users "     \
                                "SET SOCKET = ?1 "  \
                                "WHERE LOGIN = ?2",//
                            -1, &stmt, 0);///////////
    sqlite3_bind_int(stmt, 1, connfd);
    sqlite3_bind_text(stmt, 2, username, -1, SQLITE_STATIC);
    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_finalize(stmt);
    return;
}
