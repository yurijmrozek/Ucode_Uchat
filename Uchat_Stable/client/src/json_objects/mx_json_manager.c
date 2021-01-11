#include "client.h"

void mx_json_manager(char buff_in[], client_t *cli) {
    cJSON *j_responce = cJSON_Parse(buff_in);

    cJSON *j_action = cJSON_GetObjectItemCaseSensitive(j_responce,
                                                       "action");
    if (!strcmp(j_action->valuestring, "signin_responce"))
        mx_login_responce(j_responce, cli);
    if (!strcmp(j_action->valuestring, "signup_responce"))
        mx_register_responce(j_responce, cli);
    cJSON_Delete(j_responce);
}
