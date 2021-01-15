#include "server.h"

void mx_send_friend_invite(sqlite3 *db, char *username, int connfd) {
    cJSON *j_responce = cJSON_CreateObject();

    int uid = mx_get_id_socket(db, connfd);
    char *ulogin = mx_get_login_id(db, uid);
    int sockfd = mx_get_socket_login(db, username);

    cJSON_AddItemToObject(j_responce, "action",//////////////////////////
                          cJSON_CreateString("friend_invite_from_user"));
    cJSON_AddItemToObject(j_responce, "username",////////////////////////
                                  cJSON_CreateString(ulogin));
    char *jdata = cJSON_Print(j_responce);
    send_message_self(jdata, sockfd);
    free(jdata);
    free(username);
    cJSON_Delete(j_responce);
}
