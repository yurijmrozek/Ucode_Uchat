#include "client.h"

void mx_delete_message_request(client_t *cli, char *msgid) {
    cJSON *j_request = cJSON_CreateObject();
    cJSON_AddItemToObject(j_request, "action",////////////////
                          cJSON_CreateString("remove_msg_request"));
    cJSON_AddItemToObject(j_request, "msgid", cJSON_CreateString(msgid));

    char *jdata = cJSON_Print(j_request);
    
    send_message_self(jdata, cli->sockfd);
    
    free(jdata);
    cJSON_Delete(j_request);
}
