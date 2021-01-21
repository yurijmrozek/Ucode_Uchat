#include "server.h"

void mx_getup_new_message(int uid, cJSON *j_message, int sockfd, sqlite3 *db) {
    char *sender = mx_get_login_id(db, uid);
    int cid = mx_get_socket_id(db, sockfd);
    char *username = mx_get_login_id(db, cid);

    cJSON *j_responce = cJSON_CreateObject();
    cJSON_AddItemToObject(j_responce, "action",
                          cJSON_CreateString("getup_new_msg"));
    cJSON_AddItemToObject(j_responce, "message_list",
                          cJSON_CreateString(j_message->valuestring));
    cJSON_AddItemToObject(j_responce, "message_sender",
                          cJSON_CreateString(sender));
    cJSON_AddItemToObject(j_responce, "username",
                          cJSON_CreateString(username));
    char *jdata = cJSON_Print(j_responce);

    send_message_self(jdata, sockfd);
    free(jdata);
    cJSON_Delete(j_responce);

    free(username);
    free(sender);
}
