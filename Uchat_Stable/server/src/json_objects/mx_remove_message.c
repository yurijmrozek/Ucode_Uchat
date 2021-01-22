#include "server.h"

void mx_remove_message(cJSON *j_request, int connfd, sqlite3 *db) {
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_request, "username");
    cJSON *j_message = cJSON_GetObjectItemCaseSensitive(j_request, "message");

    int uid = mx_get_id_socket(db, connfd);
    int cid = mx_get_id_login(db, j_username->valuestring);

    mx_manage_message_db(db, uid, cid, j_message->valuestring, 2);
}
