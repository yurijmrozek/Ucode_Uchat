#include "server.h"

int mx_setactive_user(t_database *t_db, const gchar *username, int flag) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;
    rv = sqlite3_prepare_v2(t_db->db, "UPDATE users "    \
                                      "SET ONLINE = ?2 "  \
                                      "WHERE LOGIN = ?1;",
                                -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, flag);

    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        return 1;
    sqlite3_finalize(stmt);
    return 2;
}
