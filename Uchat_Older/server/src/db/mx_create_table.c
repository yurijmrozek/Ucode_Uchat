#include "server.h"

static void create_contact_table(t_database *t_db) {
    sqlite3_exec(t_db->db, "CREATE TABLE IF NOT EXISTS contact("             \
                           "ID          INTEGER      NOT NULL, "             \
                           "CONT        INTEGER      NOT NULL);",
                 0, 0, 0);
}

void mx_create_user_table(t_database *t_db) {
    sqlite3_stmt *stmt;

    sqlite3_exec(t_db->db, "CREATE TABLE IF NOT EXISTS users("               \
                           "ID    INTEGER PRIMARY KEY    NOT NULL,"          \
                           "LOGIN          TEXT UNIQUE   NOT NULL,"          \
                           "PASS           TEXT          NOT NULL,"          \
                           "SOCKET         INTEGER              );",
                 0, 0, 0);

    sqlite3_prepare_v2(t_db->db, "UPDATE users "
                                 "SET SOCKET = ?1 ",
                            -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, -1);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    create_contact_table(t_db);
}


