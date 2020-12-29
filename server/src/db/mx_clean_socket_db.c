#include "server.h"

int mx_clean_socket_db(t_database *t_db, int socket1) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(t_db->db, "UPDATE users "      \
                                      "SET SOCKET = ?1"     \
                                      "WHERE SOCKET = ?2",
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, 0);
    sqlite3_bind_int(stmt, 2, socket1);

    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return 1;
    }
    sqlite3_finalize(stmt);
    return 2;
}
