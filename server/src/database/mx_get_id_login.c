#include "server.h"

int mx_get_id_login(sqlite3 *db, char *username) {
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(db, "SELECT ID FROM users "  \
                                "WHERE LOGIN = ?1",///////
                              -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    int id = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    return id;
}
