#include "client.h"

void mx_cjson_parser(char recvBuff[], t_chat *chat) {
    cJSON *j_responce = cJSON_CreateObject();
    cJSON *json_type;
    if ((j_responce = cJSON_Parse(recvBuff))) {
        json_type = cJSON_GetObjectItemCaseSensitive(j_responce,
                                                     "action");
        if (!strcmp(json_type->valuestring, "login_r"))
            mx_login_handl_res(j_responce, chat);
        if (!strcmp(json_type->valuestring, "log_out"))
            mx_close_chatpage(j_responce, chat);
        if (!strcmp(json_type->valuestring, "add_cont"))
            mx_addcont_handl_res(j_responce, chat);
        if (!strcmp(json_type->valuestring, "getup_contact"))
            mx_getup_contact(j_responce, chat);
    }
    cJSON_Delete(j_responce);
}
