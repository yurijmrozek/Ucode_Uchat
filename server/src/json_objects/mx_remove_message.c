#include "server.h"

void mx_remove_message(cJSON *j_request, sqlite3 *db) {
    cJSON *j_msgid = cJSON_GetObjectItemCaseSensitive(j_request, "msgid");

    mx_manage_message_db(db, 0, 0, NULL, j_msgid->valuestring, 2);
}
