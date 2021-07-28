#include "server.h"

static sqlite3_stmt *delete(sqlite3 *db, sqlite3_stmt *stmt,
                            int uid, char *message) {
        sqlite3_prepare_v2(db, "UPDATE general                 "           \
                               "SET ID = 0                     "           \
                               "WHERE ID = ?1 AND MESSAGE = ?2 ",
                           -1, &stmt, 0);//////////////////////
        sqlite3_bind_int(stmt, 1, uid);
        sqlite3_bind_text(stmt, 2, message, -1, SQLITE_STATIC);
        return stmt;
}

static sqlite3_stmt *insert(sqlite3 *db, sqlite3_stmt *stmt,
                            int uid, char *message) {
    sqlite3_prepare_v2(db, "INSERT INTO general(ID, MESSAGE) "  \
                           "VALUES (?1, ?2); ",////////////////
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, uid);
    sqlite3_bind_text(stmt, 2, message, -1, SQLITE_STATIC);
    return stmt;
}

int mx_manage_chnl_db(sqlite3 *db, int uid, char *message, int action) {
    sqlite3_stmt *stmt = NULL;
    int rv = SQLITE_OK;

    if (action == 1)
        stmt = insert(db, stmt, uid, message);
    else if (action == 2)
        stmt = delete(db, stmt, uid, message);

    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return 1;
    }
    sqlite3_finalize(stmt);
    return 2;
}
