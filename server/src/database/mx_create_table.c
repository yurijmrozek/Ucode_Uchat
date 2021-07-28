#include "server.h"

static void chnl_tabel(sqlite3 *tmp_db) {
    sqlite3_exec(tmp_db,   "CREATE TABLE IF NOT EXISTS general(       "      \
                           "ID         INTEGER             NOT NULL,  "      \
                           "MESSAGE    TEXT                NOT NULL,  "
                           "MSGID      INTEGER PRIMARY KEY NOT NULL );",
                 0, 0, 0);//////////////////////////////////////
}

static void message_table(sqlite3 *tmp_db) {
    sqlite3_exec(tmp_db,   "CREATE TABLE IF NOT EXISTS message(      "       \
                           "ID         INTEGER             NOT NULL, "       \
                           "CONT       INTEGER             NOT NULL, "
                           "MESSAGE    TEXT                NOT NULL, "
                           "MSGID      INTEGER PRIMARY KEY NOT NULL);",
                 0, 0, 0);//////////////////////////////////////
}

static void contact_table(sqlite3 *tmp_db) {
    sqlite3_exec(tmp_db,   "CREATE TABLE IF NOT EXISTS contact("             \
                           "ID          INTEGER      NOT NULL, "             \
                           "CONT        INTEGER      NOT NULL, "
                           "STATE       INTEGER      NOT NULL);",
                 0, 0, 0);//////////////////////////////////////
}

static void user_table(sqlite3 *tmp_db) {
    sqlite3_stmt *stmt;

    sqlite3_exec(tmp_db,   "CREATE TABLE IF NOT EXISTS users("               \
                           "ID    INTEGER PRIMARY KEY    NOT NULL,"          \
                           "LOGIN          TEXT UNIQUE   NOT NULL,"          \
                           "PASS           TEXT          NOT NULL,"          \
                           "SOCKET         INTEGER              );",
                 0, 0, 0);/////////////////////////////////////////
    sqlite3_prepare_v2(tmp_db,   "UPDATE users    "                          \
                                 "SET SOCKET = ?1 ",
                       -1, &stmt, 0);//////////////////////////////
    sqlite3_bind_int(stmt, 1, -1);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void mx_create_table(sqlite3 *tmp_db) {
    user_table(tmp_db);
    contact_table(tmp_db);
    message_table(tmp_db);
    chnl_tabel(tmp_db);
}
