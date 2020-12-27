#include "server.h"

int mx_find_login_db(t_database *t_db, char *login) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(t_db->db, "SELECT ID FROM users WHERE LOGIN = ?1",
                       -1, &stmt, 0);

    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);

    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        return 1;
    sqlite3_finalize(stmt);
    return 2;
}
