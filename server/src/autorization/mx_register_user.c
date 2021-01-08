#include "server.h"

void mx_register_user(t_server *server, cJSON *j_request, int socket1) {
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_request, "username");
    cJSON *j_password = cJSON_GetObjectItemCaseSensitive(j_request, "password");
    char *username = strdup(j_username->valuestring);
    char *password = strdup(j_password->valuestring);
    bool valid = false;

    cJSON *j_responce = cJSON_CreateObject();
    
    cJSON_AddItemToObject(j_responce, "action", cJSON_CreateString("login_r"));
    if (mx_find_login_db(server->t_db, username) == 2) {
        mx_insert_user(server->t_db, username, password);
        mx_manage_socket_db(server->t_db, username, socket1);
        valid = true;
        cJSON_AddItemToObject(j_responce, "valid", cJSON_CreateString("true"));
    }
    else
        cJSON_AddItemToObject(j_responce, "valid",
                              cJSON_CreateString("us_exist"));
    
    char *jdata = cJSON_Print(j_responce);
    printf("\n\nTo responce:\n\n%s\n\n", jdata);
    write(socket1, jdata, strlen(jdata));
    if (valid)
        mx_init_client_db(server->t_db, socket1);
    cJSON_Delete(j_responce);
    free(jdata);
    free(username);
    free(password);
}
