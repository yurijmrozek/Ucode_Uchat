#include "client.h"

void mx_invite_answer_responce(cJSON *j_responce, client_t *cli) {
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_responce,
                                                         "username");
    cJSON *j_valid = cJSON_GetObjectItemCaseSensitive(j_responce, "valid");
    
    if (!strcmp(j_valid->valuestring, "true"))
        mx_notification_dialog(cli, j_username->valuestring, 'a');
    if (!strcmp(j_valid->valuestring, "false"))
        mx_notification_dialog(cli, j_username->valuestring, 'd');
}
