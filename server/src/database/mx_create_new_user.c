#include "server.h"

void mx_create_new_user(sqlite3 *db, char *username, char *password) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "INSERT INTO users(LOGIN,PASS,SOCKET) "  \
                           "VALUES (?1, ?2, ?3); ",//////////////////
                       -1, &stmt, NULL);/////////////////////////////
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, -1);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}
