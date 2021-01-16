#include "client.h"

void mx_friend_invite_from_user(cJSON *j_responce, client_t *cli) {
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_responce,
                                                         "username");
    char *username = strdup(j_username->valuestring);
    mx_insert_cntc_list(username, cli, "mail-mark-junk-symbolic");
    free(username);
}
