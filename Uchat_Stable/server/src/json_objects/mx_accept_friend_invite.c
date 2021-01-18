#include "server.h"

void mx_accept_friend_invite(cJSON *j_request, int connfd, sqlite3 *db) {
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_request, "username");
    char *username = strdup(j_username->valuestring);

    cJSON *j_responce = cJSON_CreateObject();

    mx_manage_cntc_db(db, connfd, username, 1, 2);
    mx_manage_cntc_db(db, connfd, username, 1, 1);

    mx_send_friend_invite(db, username);
    mx_send_cntc(db, connfd);

    free(username);
    cJSON_Delete(j_responce);
}
