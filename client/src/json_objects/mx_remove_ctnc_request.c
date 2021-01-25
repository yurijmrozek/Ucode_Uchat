#include "client.h"

void mx_remove_cntc_request(client_t *cli, char *username, char *type) {
    cJSON *j_request = cJSON_CreateObject();
    cJSON_AddItemToObject(j_request, "action",////////////////
                          cJSON_CreateString("remove_cntc_request"));
    cJSON_AddItemToObject(j_request, "username",//////////////
                          cJSON_CreateString(username));
    cJSON_AddItemToObject(j_request, "type",
                          cJSON_CreateString(type));
    char *jdata = cJSON_Print(j_request);
    
    send_message_self(jdata, cli->sockfd);
    
    free(jdata);
    cJSON_Delete(j_request);
}
