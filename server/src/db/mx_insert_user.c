#include "server.h"

void mx_insert_user(t_database *t_db, char *username, char *password) {
    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(t_db->db, "INSERT INTO users(LOGIN,PASS) "  \
                                 "VALUES (?1, ?2); ",
                       -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}
