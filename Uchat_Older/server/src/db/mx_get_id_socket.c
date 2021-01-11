#include "server.h"

int mx_get_id_socket(t_database *t_db, int socket1) {
    sqlite3_stmt *stmt;
    gint32 rv = 0;

    rv = sqlite3_prepare_v3(t_db->db, "SELECT ID FROM users "  \
                                      "WHERE SOCKET = ?1",
                            -1, 0, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, socket1);
    sqlite3_step(stmt);
    int id = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    return id;
}
