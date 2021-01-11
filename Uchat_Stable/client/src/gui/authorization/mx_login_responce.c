#include "client.h"

void mx_login_responce(cJSON *j_responce, client_t *cli) {
    cJSON *j_valid = cJSON_GetObjectItemCaseSensitive(j_responce, "valid");
    cJSON *j_reason = cJSON_GetObjectItemCaseSensitive(j_responce, "reason");
    
    if (!strcmp(j_valid->valuestring, "true")
        && !strcmp(j_reason->valuestring, "true_credentials"))
        mx_creden_accepted(j_responce, cli);
    else if (!strcmp(j_valid->valuestring, "false")) {
        if (!strcmp(j_reason->valuestring, "user_already_online"))
            printf("User already online\n");
        else if (!strcmp(j_reason->valuestring, "invalid_credentials_given"))
            printf("Wrong log or password\n");
    }
}
