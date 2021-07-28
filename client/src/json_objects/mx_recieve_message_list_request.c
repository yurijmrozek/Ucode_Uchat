#include "client.h"

void mx_recieve_message_list_request(char *login, client_t *cli) {
    cJSON *j_request = cJSON_CreateObject();
    cJSON_AddItemToObject(j_request, "action",////////////////
                          cJSON_CreateString("get_message"));
    cJSON_AddItemToObject(j_request, "username",//////////////
                          cJSON_CreateString(login));
    char *jdata = cJSON_Print(j_request);

    send_message_self(jdata, cli->sockfd);
    free(jdata);
    cJSON_Delete(j_request);
}
