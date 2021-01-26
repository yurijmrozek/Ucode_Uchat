#include "server.h"

void mx_add_new_cntc_responce(cJSON *j_request, int connfd, sqlite3 *db) {
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_request, "username");
    char *username = strdup(j_username->valuestring);
    int uid = mx_get_id_socket(db, connfd);
    char *uname = mx_get_login_id(db, uid);

    cJSON *j_responce = cJSON_CreateObject();
    cJSON_AddItemToObject(j_responce, "action",///////////////////////
                          cJSON_CreateString("add_new_cntc_responce"));
    if (strcmp(uname, username) != 0) {
        if (mx_find_similar_cntc_db(db, username, connfd) != 1) {
            if (mx_find_invite(db, username, connfd) != 1
                && mx_finde_invite_rev(db, username, connfd) != 1) {
                if (mx_search_user(db, username) == 1) {
                    mx_manage_cntc_db(db, connfd, username, 0, 1);
                    if (mx_check_uonline_status(db, username) != 1) 
                        mx_send_friend_invite(db, username);
                    cJSON_AddItemToObject(j_responce, "username",//////
                                          cJSON_CreateString(username));
                    cJSON_AddItemToObject(j_responce, "valid",///////
                                          cJSON_CreateString("true"));
                    cJSON_AddItemToObject(j_responce, "reason",//////
                                          cJSON_CreateString("true_credentials"));
                }
                else {
                    cJSON_AddItemToObject(j_responce, "username",//////
                                          cJSON_CreateString(username));
                    cJSON_AddItemToObject(j_responce, "valid",////////
                                          cJSON_CreateString("false"));
                    cJSON_AddItemToObject(j_responce, "reason",////////
                                          cJSON_CreateString("invalid_"  \
                                                            "credentials_given"));
                }
            }
            else {
                cJSON_AddItemToObject(j_responce, "username",//////
                                      cJSON_CreateString(username));
                cJSON_AddItemToObject(j_responce, "valid",////////
                                      cJSON_CreateString("false"));
                cJSON_AddItemToObject(j_responce, "reason",////////
                                      cJSON_CreateString("invite_exist"));
            }
        }
        else {
            cJSON_AddItemToObject(j_responce, "username",//////
                                  cJSON_CreateString(username));
            cJSON_AddItemToObject(j_responce, "valid",////////
                                  cJSON_CreateString("false"));
            cJSON_AddItemToObject(j_responce, "reason",////////
                                  cJSON_CreateString("user_exist"));
        }
    }
    else {
        cJSON_AddItemToObject(j_responce, "username",//////
                              cJSON_CreateString(username));
        cJSON_AddItemToObject(j_responce, "valid",////////
                              cJSON_CreateString("false"));
        cJSON_AddItemToObject(j_responce, "reason",////////
                              cJSON_CreateString("SHIZA"));
    }
    char *jdata = cJSON_Print(j_responce);

    send_message_self(jdata, connfd);
    free(jdata);
    free(username);
    cJSON_Delete(j_responce);
}
