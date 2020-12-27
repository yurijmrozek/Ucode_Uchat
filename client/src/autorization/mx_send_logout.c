#include "client.h"

void mx_send_logout(t_chat *chat) {
    cJSON *j_logout = cJSON_CreateObject();
    cJSON_AddItemToObject(j_logout, "action", cJSON_CreateString("log_out"));
    cJSON_AddItemToObject(j_logout, "username",
                          cJSON_CreateString(chat->username));
    char *jdata = cJSON_Print(j_logout);
    write(chat->sockfd, jdata, strlen(jdata));
    cJSON_Delete(j_logout);
    free(jdata);
}
