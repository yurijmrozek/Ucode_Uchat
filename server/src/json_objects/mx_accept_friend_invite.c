#include "server.h"

void mx_accept_friend_invite(cJSON *j_request, int connfd, sqlite3 *db) {
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_request, "username");
    char *username = strdup(j_username->valuestring);

    cJSON *j_responce = cJSON_CreateObject();

    int uid = mx_get_id_login(db, username);
    int sockfd = mx_get_socket_id(db, uid);
    int cid = mx_get_id_socket(db, connfd);
    char *ulogin = mx_get_login_id(db, cid);

    mx_manage_cntc_db(db, connfd, username, 1, 2);
    mx_manage_cntc_db(db, connfd, username, 1, 1);

    mx_send_cntc(db, sockfd);
    mx_send_cntc(db, connfd);

    cJSON_AddItemToObject(j_responce, "action",////////////////
                          cJSON_CreateString("invite_answer"));
    cJSON_AddItemToObject(j_responce, "username",//////////////
                          cJSON_CreateString(ulogin));/////////
    cJSON_AddItemToObject(j_responce, "valid",/////////////////
                          cJSON_CreateString("true"));/////////
    char *jdata = cJSON_Print(j_responce);

    send_message_self(jdata, sockfd);

    free(ulogin);
    free(jdata);
    free(username);
    cJSON_Delete(j_responce);
}
