#include "server.h"

void mx_insert_new_message(cJSON *j_request, int connfd, sqlite3 *db) {
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_request, "username");
    cJSON *j_message = cJSON_GetObjectItemCaseSensitive(j_request, "message");

    int uid = mx_get_id_socket(db, connfd);
    int cid = mx_get_id_login(db, j_username->valuestring);
    
    mx_manage_message_db(db, uid, cid, j_message->valuestring, 1);
    
    if (mx_check_uonline_status(db, j_username->valuestring) != 1) {
        int sockfd = mx_get_socket_id(db, cid);
        mx_getup_new_message(uid, j_message, sockfd, db);
    }
}
