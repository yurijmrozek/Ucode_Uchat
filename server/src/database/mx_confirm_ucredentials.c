#include "server.h"

int mx_confirm_ucredentials(sqlite3 *db, char *username, char *password) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "SELECT ID FROM users WHERE LOGIN = ?1 "  \
                                "AND PASS = ?2",///////////////////////////
                            -1, &stmt, 0);////////////////////////////////
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    
    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return 1;
    }
    sqlite3_finalize(stmt);
    return 2;
}
