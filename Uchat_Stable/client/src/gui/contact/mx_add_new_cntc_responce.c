#include "client.h"

void mx_add_new_cntc_responce(cJSON *j_responce, client_t *cli) {
    cJSON *j_valid = cJSON_GetObjectItemCaseSensitive(j_responce, "valid");
    cJSON *j_reason = cJSON_GetObjectItemCaseSensitive(j_responce, "reason");
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_responce,
                                                         "username");
    char *username = strdup(j_username->valuestring);
    if (!strcmp(j_valid->valuestring, "true")
        && !strcmp(j_reason->valuestring, "true_credentials")) {
        mx_insert_cntc_list(username, cli, "contact-new");
        mx_sending_invite_dialog(cli, 't');
    }
    else if (!strcmp(j_valid->valuestring, "false")) {
        if (!strcmp(j_reason->valuestring, "invalid_credentials_given"))
            mx_sending_invite_dialog(cli, 'u');
        else if (!strcmp(j_reason->valuestring, "user_exist"))
            mx_sending_invite_dialog(cli, 'e');
        else if (!strcmp(j_reason->valuestring, "invite_exist"))
            mx_sending_invite_dialog(cli, 'f');
        else if (!strcmp(j_reason->valuestring, "SHIZA"))
            mx_sending_invite_dialog(cli, '6');
    }
    free(username);
}
