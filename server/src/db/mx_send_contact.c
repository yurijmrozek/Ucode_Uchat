#include "server.h"

char **mx_send_contact(t_database *t_db, int socket1) {
    char **contarr = (char **)malloc(sizeof(char *) * 8);
    int j = -1;
    sqlite3_stmt *stmt;
    gint32 rv = 0;

    int uid = mx_get_id_socket(t_db, socket1);
    rv = sqlite3_prepare_v2(t_db->db, "SELECT * FROM contact WHERE ID = ?1",
                            -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, uid);
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        contarr[++j] = strdup(mx_get_login_id(t_db,
                               sqlite3_column_int64(stmt, 1)));
    return contarr;
}
