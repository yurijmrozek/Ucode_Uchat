#include "client.h"

void mx_accept_cntc_request(client_t *cli, char *login) {
    cJSON *j_request = cJSON_CreateObject();
    cJSON_AddItemToObject(j_request, "action",////////////////
                          cJSON_CreateString("accept_cntc_invite"));
    cJSON_AddItemToObject(j_request, "username",//////////////
                          cJSON_CreateString(login));
    char *jdata = cJSON_Print(j_request);

    send_message_self(jdata, cli->sockfd);
    free(jdata);
    cJSON_Delete(j_request);
}
