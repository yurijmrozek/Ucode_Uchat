#include "server.h"

void mx_login_responce(t_server *server, cJSON *j_request, int socket1) {
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_request, "username");
    cJSON *j_password = cJSON_GetObjectItemCaseSensitive(j_request, "password");
    char *username = strdup(j_username->valuestring);
    char *password = strdup(j_password->valuestring);
    cJSON *j_responce = cJSON_CreateObject();

    cJSON_AddItemToObject(j_responce, "action", cJSON_CreateString("login_r"));

    if (mx_find_logpass_db(server->t_db, username, password) == 1) {
        if (mx_user_online(server->t_db, username) == 1) {
            mx_manage_socket_db(server->t_db, username, socket1);
            // char *contact = mx_send_contacts(server->t_db, socket1);
            cJSON_AddItemToObject(j_responce, "valid",
                                  cJSON_CreateString("true"));
            // if (contact)
            //     cJSON_AddItemToObject(j_responce, "contacts",
            //                           cJSON_CreateString(contact));
        }
        else
            cJSON_AddItemToObject(j_responce, "valid",
                                  cJSON_CreateString("busy"));
    }
    else
        cJSON_AddItemToObject(j_responce, "valid", cJSON_CreateString("false"));
    char *jdata = cJSON_Print(j_responce);
    printf("\n\nTo responce:\n\n%s\n\n", jdata);
    write(socket1, jdata, strlen(jdata));
    cJSON_Delete(j_responce);
    free(jdata);
}
