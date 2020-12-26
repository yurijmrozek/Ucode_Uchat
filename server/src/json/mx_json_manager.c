#include "server.h"

void mx_json_manager(char Buffer[1024], t_server *server, int socket1) {
    cJSON *j_request = cJSON_CreateObject();

    j_request = cJSON_Parse(Buffer);
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_request, "action");
    char *action = strdup(json_type->valuestring);

    if (!strcmp(action, "login")) {
        mx_login_responce(j_request, socket1);
    }
    if (!strcmp(action, "register"))
        mx_register_user(j_request, socket1);
}
