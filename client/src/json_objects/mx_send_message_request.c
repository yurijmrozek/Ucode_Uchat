#include "client.h"

void mx_send_message_request(gchar *message, char *username, client_t *cli) {
    cJSON *j_request = cJSON_CreateObject();
    cJSON_AddItemToObject(j_request, "action",////////////////
                          cJSON_CreateString("send_message"));
    cJSON_AddItemToObject(j_request, "username",//////////////
                          cJSON_CreateString(username));
    cJSON_AddItemToObject(j_request, "message",///////////////
                          cJSON_CreateString(message));
    char *jdata = cJSON_Print(j_request);

    send_message_self(jdata, cli->sockfd);
    free(jdata);
    cJSON_Delete(j_request);
}
