#include "client.h"

<<<<<<< HEAD
void mx_remove_cntc_request(client_t *cli, char *username, char *flag) {
=======
void mx_remove_cntc_request(client_t *cli, char *username) {
>>>>>>> 362fc53b3134ed81fabb4f5be9246112b6c5b010
    cJSON *j_request = cJSON_CreateObject();
    cJSON_AddItemToObject(j_request, "action",////////////////
                          cJSON_CreateString("remove_cntc_request"));
    cJSON_AddItemToObject(j_request, "username",//////////////
                          cJSON_CreateString(username));
<<<<<<< HEAD
    cJSON_AddItemToObject(j_request, "type",//////////////////
                          cJSON_CreateString(flag));
=======
>>>>>>> 362fc53b3134ed81fabb4f5be9246112b6c5b010
    char *jdata = cJSON_Print(j_request);
    
    send_message_self(jdata, cli->sockfd);
    free(jdata);
    cJSON_Delete(j_request);
}
