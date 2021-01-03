#include "server.h"

void mx_add_contact(t_server *server, cJSON *j_request, int socket1) {
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_request, "login");
    char *login = strdup(j_username->valuestring);


    cJSON *j_responce = cJSON_CreateObject();
    cJSON_AddItemToObject(j_responce, "action", cJSON_CreateString("add_cont"));

    if (mx_find_similar_cont(server->t_db, login, socket1) != 1) {
        if (mx_find_login_db(server->t_db, login) == 1) {
            mx_add_contact_db(server->t_db, login, socket1);
            cJSON_AddItemToObject(j_responce, "login",
                                  cJSON_CreateString(login));
            cJSON_AddItemToObject(j_responce, "valid",
                                  cJSON_CreateString("true"));
        }
        else {
            cJSON_AddItemToObject(j_responce, "login",
                                  cJSON_CreateString(login));
            cJSON_AddItemToObject(j_responce, "valid",
                                  cJSON_CreateString("false"));
        }
    }
    else {
        cJSON_AddItemToObject(j_responce, "login",
                              cJSON_CreateString(login));
            cJSON_AddItemToObject(j_responce, "valid",
                              cJSON_CreateString("exist"));
    }
    char *jdata = cJSON_Print(j_responce);
    printf("\n\nTo responce:\n\n%s\n\n", jdata);
    write(socket1, jdata, strlen(jdata));
    cJSON_Delete(j_responce);
    free(jdata);
}
