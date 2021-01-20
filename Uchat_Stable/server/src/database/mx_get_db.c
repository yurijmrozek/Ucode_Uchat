#include "server.h"

sqlite3 *mx_get_db(sqlite3 *tmp_db) {
    int rc = sqlite3_open("database.db", &tmp_db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(tmp_db));
        return NULL;
    }
    mx_create_table(tmp_db);
    return tmp_db;
}
