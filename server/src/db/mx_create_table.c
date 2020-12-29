#include "server.h"

int mx_create_user_table(t_database *t_db) {
    sqlite3_exec(t_db->db, "CREATE TABLE IF NOT EXISTS users("               \
                           "ID    INTEGER PRIMARY KEY    NOT NULL,"          \
                           "LOGIN          TEXT UNIQUE   NOT NULL,"          \
                           "PASS           TEXT          NOT NULL,"          \
                           "SOCKET         INTEGER       ,"  \
                           "DATE           INTEGER       NOT NULL);",
                 0, 0, 0);
    return 1;
}


