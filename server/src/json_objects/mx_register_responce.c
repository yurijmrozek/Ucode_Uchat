#include "server.h"

void mx_register_responce(cJSON *j_request, int connfd, sqlite3 *db) {
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_request, "username");
    cJSON *j_password = cJSON_GetObjectItemCaseSensitive(j_request, "password");
    char *username = strdup(j_username->valuestring);
    char *password = strdup(j_password->valuestring);

    cJSON *j_responce = cJSON_CreateObject();
    if (mx_search_user(db, username) == 2) {
        mx_create_new_user(db, username, password);
        mx_login_responce(j_request, connfd, db);
    }
    else {
        cJSON_AddItemToObject(j_responce, "action",/////////////////
                          cJSON_CreateString("signup_responce"));//
        cJSON_AddItemToObject(j_responce, "valid",//////////////////
                              cJSON_CreateString("false"));////////
        cJSON_AddItemToObject(j_responce, "reason",/////////////////
                              cJSON_CreateString("user_exist"));///
        char *jdata = cJSON_Print(j_responce);

        send_message_self(jdata, connfd);
        free(jdata);
    }
    free(username);
    free(password);
    cJSON_Delete(j_responce);
}
