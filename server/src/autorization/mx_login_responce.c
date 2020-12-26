#include "server.h"

void mx_login_responce(cJSON *j_request, int socket1) {
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_request, "username");
    cJSON *j_password = cJSON_GetObjectItemCaseSensitive(j_request, "password");
    char *username = strdup(j_username->valuestring);
    char *password = strdup(j_password->valuestring);

    //diff with db
    cJSON *j_responce = cJSON_CreateObject();
    // //if diff no write true, else false
    cJSON_AddItemToObject(j_responce, "action", cJSON_CreateString("login_r"));
    cJSON_AddItemToObject(j_responce, "valid", cJSON_CreateString("true"));
    
    char *jdata = cJSON_Print(j_responce);
    printf("\n\nTo responce:\n\n%s\n\n", jdata);
    write(socket1, jdata, strlen(jdata));
    cJSON_Delete(j_responce);
    free(jdata);
}
