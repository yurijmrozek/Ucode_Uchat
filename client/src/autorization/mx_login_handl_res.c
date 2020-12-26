#include "client.h"

void mx_login_handl_res(cJSON *j_responce, t_chat *chat) {
    cJSON *j_valid = cJSON_GetObjectItemCaseSensitive(j_responce, "valid");
    char *valid = strdup(j_valid->valuestring);
    if (strcmp(valid, "true") == 0)
        autorized_accept(chat);
}
