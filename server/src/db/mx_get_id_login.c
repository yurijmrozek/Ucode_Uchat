#include "server.h"

int mx_get_id_login(t_database *t_db, char *login) {
    sqlite3_stmt *stmt;
    gint32 rv = 0;

    rv = sqlite3_prepare_v3(t_db->db, "SELECT ID FROM users "  \
                                      "WHERE LOGIN = ?1",
                            -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    int id = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    return id;
}
