#include "server.h"

static sqlite3_stmt *delete(sqlite3 *db, sqlite3_stmt *stmt,
                            int uid, int cid, char *message) {
        sqlite3_prepare_v2(db, "UPDATE message              "           \
                               "SET ID = 0,                 "           \
                               "CONT = 0                    "           \
                               "WHERE ID = ?1 AND CONT = ?2 "           \
                               "AND MESSAGE = ?3            "
                               "LIMIT 1",
                           -1, &stmt, 0);//////////////////////
        sqlite3_bind_int(stmt, 1, uid);
        sqlite3_bind_int(stmt, 2, cid);
        sqlite3_bind_text(stmt, 3, message, -1, SQLITE_STATIC);
        return stmt;
}

static sqlite3_stmt *insert(sqlite3 *db, sqlite3_stmt *stmt,
                            int uid, int cid, char *message) {
    sqlite3_prepare_v2(db, "INSERT INTO message(ID,CONT,MESSAGE) "  \
                           "VALUES (?1, ?2, ?3); ",////////////////
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, uid);
    sqlite3_bind_int(stmt, 2, cid);
    sqlite3_bind_text(stmt, 3, message, -1, SQLITE_STATIC);
    return stmt;
}

int mx_manage_message_db(sqlite3 *db, int uid, int cid, char *message,
                         int action) {
    sqlite3_stmt *stmt = NULL;
    int rv = SQLITE_OK;

    if (action == 1)
        stmt = insert(db, stmt, uid, cid, message);
    else if (action == 2)
        stmt = delete(db, stmt, uid, cid, message);

    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return 1;
    }
    sqlite3_finalize(stmt);
    return 2;
}
