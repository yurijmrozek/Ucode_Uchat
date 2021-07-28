#include "server.h"

void mx_login_responce(cJSON *j_request, int connfd, sqlite3 *db) {
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_request, "username");
    cJSON *j_password = cJSON_GetObjectItemCaseSensitive(j_request, "password");
    char *username = strdup(j_username->valuestring);
    char *password = strdup(j_password->valuestring);
    bool valid = false;

    cJSON *j_responce = cJSON_CreateObject();
    cJSON_AddItemToObject(j_responce, "action",/////////////////
                          cJSON_CreateString("signin_responce"));
    if (mx_confirm_ucredentials(db, username, password) == 1) {
        if (mx_check_uonline_status(db, username) == 1) {
            mx_insert_client_socket(db, username, connfd);
            cJSON_AddItemToObject(j_responce, "valid",//////////
                                  cJSON_CreateString("true"));
            cJSON_AddItemToObject(j_responce, "reason",/////////
                                  cJSON_CreateString("true_credentials"));
            valid = true;
        }
        else {
            cJSON_AddItemToObject(j_responce, "valid",//////////
                                  cJSON_CreateString("false"));
            cJSON_AddItemToObject(j_responce, "reason",/////////
                                  cJSON_CreateString("user_already_online"));
        }
    }
    else {
        cJSON_AddItemToObject(j_responce, "valid", cJSON_CreateString("false"));
        cJSON_AddItemToObject(j_responce, "reason",/////////
                              cJSON_CreateString("invalid_credentials_given"));
    }
    char *jdata = cJSON_Print(j_responce);

    send_message_self(jdata, connfd);   
    free(jdata);
    free(username);
    free(password);
    cJSON_Delete(j_responce);

    if (valid)
        mx_init_client_db(db, connfd);  
}
