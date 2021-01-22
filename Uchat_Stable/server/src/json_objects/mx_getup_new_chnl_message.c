#include "server.h"

void mx_getup_new_chnl_message(int uid, cJSON *j_message, sqlite3 *db) {
    char *sender = mx_get_login_id(db, uid);
    int connfd = mx_get_socket_id(db, uid);

    cJSON *j_responce = cJSON_CreateObject();
    cJSON_AddItemToObject(j_responce, "action",
                          cJSON_CreateString("getup_new_chnl_msg"));
    cJSON_AddItemToObject(j_responce, "message_list",
                          cJSON_CreateString(j_message->valuestring));
    cJSON_AddItemToObject(j_responce, "message_sender",
                          cJSON_CreateString(sender));

    send_message_all(j_responce, db, connfd);
    cJSON_Delete(j_responce);

    free(sender);
}
