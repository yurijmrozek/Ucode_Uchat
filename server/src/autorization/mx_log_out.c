#include "server.h"

void mx_log_out(t_server *server, cJSON *j_request, int socket1) {
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_request, "username");
    char *username = strdup(j_username->valuestring);

    mx_setactive_user(server->t_db, username, 0);
}
