#include "server.h"

static void get_id_user(t_database *t_db) {
    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(t_db->db, "select id from users where date = ?1",
                       -1, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, t_db->u_date);
    sqlite3_step(stmt);
    t_db->u_id = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
}

void mx_insert_user(t_database *t_db, char *username, char *password) {
    sqlite3_stmt *stmt;

    t_db->u_date = mx_get_time(DB_MILISECOND);
    sqlite3_prepare_v2(t_db->db, "INSERT INTO users(LOGIN,PASS,DATE) "  \
                                 "VALUES (?1, ?2, ?3); ",
                       -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 3, t_db->u_date);
    
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    get_id_user(t_db);
}
