#include "server.h"

int mx_find_invite(sqlite3 *db, char *username, int connfd) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;
    int uid, cid;

    uid = mx_get_id_socket(db, connfd);
    cid = mx_get_id_login(db, username);

    rv = sqlite3_prepare_v2(db, "SELECT ID FROM contact WHERE ID = ?1 "  \
                                "AND CONT = ?2 AND STATE = 0",
                            -1, &stmt, 0);
    sqlite3_bind_int64(stmt, 1, cid);
    sqlite3_bind_int64(stmt, 2, uid);

    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return 1;
    }
    sqlite3_finalize(stmt);
    return 2;
}
