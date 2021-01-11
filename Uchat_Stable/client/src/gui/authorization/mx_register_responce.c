#include "client.h"

void mx_register_responce(cJSON *j_responce, client_t *cli) {
    cJSON *j_valid = cJSON_GetObjectItemCaseSensitive(j_responce, "valid");
    cJSON *j_reason = cJSON_GetObjectItemCaseSensitive(j_responce, "reason");
    
    if (!strcmp(j_valid->valuestring, "false")) {
        if (!strcmp(j_reason->valuestring, "user_exist"))
            printf("User exist( Try another username\n");
    }
}
