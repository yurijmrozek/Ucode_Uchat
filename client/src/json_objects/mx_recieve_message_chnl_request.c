#include "client.h"

void mx_recieve_message_chnl_request(client_t *cli) {
    cJSON *j_request = cJSON_CreateObject();
    cJSON_AddItemToObject(j_request, "action",////////////////
                          cJSON_CreateString("get_chnl_message"));
    char *jdata = cJSON_Print(j_request);

    send_message_self(jdata, cli->sockfd);
    free(jdata);
    cJSON_Delete(j_request);
}
