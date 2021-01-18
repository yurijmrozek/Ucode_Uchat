#include "server.h"

void mx_send_friend_invite(sqlite3 *db, char *username) {
    int cid = mx_get_id_login(db, username);
    int sockfd = mx_get_socket_id(db, cid);

    cJSON *j_responce = cJSON_CreateObject();
    cJSON_AddItemToObject(j_responce, "action",////////////////////////
                          cJSON_CreateString("recieved_friend_invite"));
    char *j_data = cJSON_Print(j_responce);

    send_message_self(j_data, sockfd);
    mx_send_cntc(db, sockfd);
    free(j_data);
    cJSON_Delete(j_responce);
}
