#include "client.h"

void mx_cjson_parser(char recvBuff[1024], t_chat *chat) {
    cJSON *j_responce = cJSON_CreateObject();
    j_responce = cJSON_Parse(recvBuff);
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "action");
    char *action = strdup(json_type->valuestring);


    if (!strcmp(action, "login_r"))
        mx_login_handl_res(j_responce, chat);
    if (!strcmp(action, "log_out"))
        mx_close_client(j_responce, chat);
    
}
