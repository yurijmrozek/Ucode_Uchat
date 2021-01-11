#include "server.h"

int mx_oc_db(t_database *t_db) {
    /* Open database */
    int rc = sqlite3_open("test.db", &t_db->db);
    
    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(t_db->db));
        return 2;
    }
    mx_create_user_table(t_db);
    return 1;
}
