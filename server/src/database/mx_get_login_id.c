#include "server.h"

char *mx_get_login_id(sqlite3 *db, int id) {
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(db, "SELECT LOGIN FROM users "  \
                                "WHERE ID = ?1",
                            -1, 0, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, id);
    sqlite3_step(stmt);
    char *login = strdup((char *)sqlite3_column_text(stmt, 0));
    sqlite3_finalize(stmt);
    return login;
}
