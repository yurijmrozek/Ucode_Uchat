#include "server.h"

static sqlite3_stmt *delete_rev(sqlite3 *db, sqlite3_stmt *stmt,
                            int uid, int cid, int state) {
    sqlite3_prepare_v2(db, "UPDATE contact "              \
                           "SET STATE = ?1 "              \
                           "WHERE ID = ?2 AND CONT = ?3",
                       -1, &stmt, 0);//////////////////////
    sqlite3_bind_int(stmt, 1, state);
    sqlite3_bind_int(stmt, 2, uid);
    sqlite3_bind_int(stmt, 3, cid);
    return stmt;
}

static sqlite3_stmt *delete(sqlite3 *db, sqlite3_stmt *stmt,
                            int uid, int cid, int state) {
    sqlite3_prepare_v2(db, "UPDATE contact "              \
                           "SET STATE = ?1 "              \
                           "WHERE ID = ?2 AND CONT = ?3",
                       -1, &stmt, 0);//////////////////////
    sqlite3_bind_int(stmt, 1, state);
    sqlite3_bind_int(stmt, 2, cid);
    sqlite3_bind_int(stmt, 3, uid);
    return stmt;
}

static sqlite3_stmt *update(sqlite3 *db, sqlite3_stmt *stmt,
                            int uid, int cid, int state) {
    sqlite3_prepare_v2(db, "UPDATE contact "              \
                           "SET STATE = ?1 "              \
                           "WHERE ID = ?2 AND CONT = ?3 " \
                           "AND STATE = 0 ",
                       -1, &stmt, 0);//////////////////////
    sqlite3_bind_int(stmt, 1, state);
    sqlite3_bind_int(stmt, 2, cid);
    sqlite3_bind_int(stmt, 3, uid);
    return stmt;
}

static sqlite3_stmt *insert(sqlite3 *db, sqlite3_stmt *stmt,
                            int uid, int cid, int state) {
    sqlite3_prepare_v2(db, "INSERT INTO contact(ID,CONT,STATE) "  \
                           "VALUES (?1, ?2, ?3); ",////////////////
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, uid);
    sqlite3_bind_int(stmt, 2, cid);
    sqlite3_bind_int(stmt, 3, state);
    return stmt;
}

int mx_manage_cntc_db(sqlite3 *db, int connfd,///////////////
                       char *username, int state, int action) {
    sqlite3_stmt *stmt = NULL;
    int rv = SQLITE_OK;

    int uid = mx_get_id_socket(db, connfd);
    int cid = mx_get_id_login(db, username);

    if (action == 1)
        stmt = insert(db, stmt, uid, cid, state);
    else if (action == 2)
        stmt = update(db, stmt, uid, cid, state);
    else if (action == 3)
        stmt = delete(db, stmt, uid, cid, state);
    else if (action == 4)
        stmt = delete_rev(db, stmt, uid, cid, state);

    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return 1;
    }
    sqlite3_finalize(stmt);
    return 2;
}
