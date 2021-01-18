#include "server.h"

void mx_json_manager(char buff_in[], int connfd, client_t *cli) {
    cJSON *j_request = cJSON_CreateObject();
    
    j_request = cJSON_Parse(buff_in);
    cJSON *action = cJSON_GetObjectItemCaseSensitive(j_request, "action");
    if (!strcmp(action->valuestring, "signin_user"))
        mx_login_responce(j_request, connfd, cli->db);
    else if (!strcmp(action->valuestring, "signup_user"))
        mx_register_responce(j_request, connfd, cli->db);
    else if (!strcmp(action->valuestring, "logout_user"))
        mx_logout_event_db(connfd, cli->db);
    else if (!strcmp(action->valuestring, "add_new_cntc_user"))
        mx_add_new_cntc_responce(j_request, connfd, cli->db);
    else if (!strcmp(action->valuestring, "accept_cntc_invite"))
        mx_accept_friend_invite(j_request, connfd, cli->db);
    cJSON_Delete(j_request);
}
