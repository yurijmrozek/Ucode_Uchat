#include "server.h"

int mx_search_user(sqlite3 *db, char *username) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "SELECT ID FROM users WHERE LOGIN = ?1",
                            -1, &stmt, 0);//////////////////////////////
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        return 1;
    sqlite3_finalize(stmt);
    return 2;
}
