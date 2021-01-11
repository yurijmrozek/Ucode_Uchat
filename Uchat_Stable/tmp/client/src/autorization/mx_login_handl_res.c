#include "client.h"

void mx_login_handl_res(cJSON *j_responce, t_chat *chat) {
    cJSON *j_valid = cJSON_GetObjectItemCaseSensitive(j_responce, "valid");
    char *valid = strdup(j_valid->valuestring);

    if (!strcmp(valid, "true"))
        autorized_accept(chat);
    else if (!strcmp(valid, "us_exist"))
        autorized_decline(chat, 'e');
    else if (!strcmp(valid, "busy"))
        autorized_decline(chat, 'b');
    else
        autorized_decline(chat, 'n');
    free(chat->username);
    free(valid);
}
