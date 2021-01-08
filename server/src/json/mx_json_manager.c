#include "server.h"

void mx_json_manager(char Buffer[2048], t_server *server, int socket1) {
    cJSON *j_request = cJSON_CreateObject();

    if ((j_request = cJSON_Parse(Buffer))) {
        cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_request,
                                                            "action");
        if (!strcmp(json_type->valuestring, "login"))
            mx_login_responce(server, j_request, socket1);
        if (!strcmp(json_type->valuestring, "register"))
            mx_register_user(server, j_request, socket1);
        if (!strcmp(json_type->valuestring, "log_out"))
            mx_log_out(server, socket1);
        if (!strcmp(json_type->valuestring, "add_cont"))
            mx_add_contact(server, j_request, socket1);
    }
    cJSON_Delete(j_request);
}
