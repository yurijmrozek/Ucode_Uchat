#include "server.h"

int mx_find_similar_cont(t_database *t_db, char *login, int socket1) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;
    int uid, cid;
    
    uid = mx_get_id_socket(t_db, socket1);
    cid = mx_get_id_login(t_db, login);

    rv = sqlite3_prepare_v2(t_db->db, "SELECT ID FROM contact WHERE ID = ?1 "
                                      "AND CONT = ?2",
                       -1, &stmt, 0);
    sqlite3_bind_int64(stmt, 1, uid);
    sqlite3_bind_int64(stmt, 2, cid);

    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return 1;
    }
    sqlite3_finalize(stmt);
    return 2;
}
