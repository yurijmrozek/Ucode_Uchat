#include "server.h"

int mx_user_online(t_database *t_db, char *username) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(t_db->db, "SELECT ID FROM users WHERE LOGIN = ?1 "
                                      "AND SOCKET = ?2",
                       -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, -1);

    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return 1;
    }
    sqlite3_finalize(stmt);
    return 2;
}
