#include "client.h"

void mx_add_cntc_request(client_t *cli, char *username) {
    for (int i = 0; username[i]; i++)
        username[i] = tolower(username[i]);
    cJSON *j_request = cJSON_CreateObject();
    cJSON_AddItemToObject(j_request, "action",////////////////////
                          cJSON_CreateString("add_new_cntc_user"));
    cJSON_AddItemToObject(j_request, "username",//////////////////
                          cJSON_CreateString(username));//////////
    char *jdata = cJSON_Print(j_request);

    send_message_self(jdata, cli->sockfd);
    free(jdata);
    cJSON_Delete(j_request);
}
