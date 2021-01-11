#include "server.h"

void mx_add_contact_db(t_database *t_db, char *login, int socket1) {
    sqlite3_stmt *stmt;
    int uid, cid;
    
    uid = mx_get_id_socket(t_db, socket1);
    cid = mx_get_id_login(t_db, login);

    sqlite3_prepare_v2(t_db->db, "INSERT INTO contact(ID, CONT) "  \
                                 "VALUES (?1, ?2); ",
                       -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, uid);
    sqlite3_bind_int(stmt, 2, cid);
    
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}
