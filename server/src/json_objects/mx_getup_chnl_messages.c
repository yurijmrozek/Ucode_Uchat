#include "server.h"

static char *strnew(const int size) {
    char *strnew = malloc(size < 0 ? size : size + 1);

    for (int i = 0; strnew[i] && i <= size; ++i)
        strnew[i] = '\0';
    return strnew; 
}

static char *strjoin(const char *s1, const char *s2) {
    char *result = NULL;

    if (!s1 && !s2)
        return NULL;
    else if (!s1)
        return strdup(s2);
    else if (!s2)
        return strdup(s1);
    
    result = strnew(strlen(s1) + strlen(s2));
    strcpy(result, s1);
    result = strcat(result, s2);
    return result;
}

static char *get_sender(sqlite3 *db) {
    char **sendarr = (char **)malloc(sizeof(char *) * 10);
    char *sender = NULL;
    int j = -1;
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v2(db, "SELECT * FROM general",
                            -1, &stmt, NULL);    
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        sendarr[++j] = strdup(mx_get_login_id(db,
                              sqlite3_column_int64(stmt, 0)));
        sender = strjoin(sender, sendarr[j]);
        sender = strjoin(sender, ",");
    }
    free(sendarr);
    return sender;
}

static char *get_messages(sqlite3 *db) {
    char **msgarr = (char **)malloc(sizeof(char *) * 10);
    char *messages = NULL;
    int j = -1;
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v2(db, "SELECT * FROM general",
                            -1, &stmt, NULL);
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        msgarr[++j] = strdup((char *)sqlite3_column_text(stmt, 1));
        messages = strjoin(messages, msgarr[j]);
        messages = strjoin(messages, "~");
    }
    free(msgarr);
    return messages;
}

void mx_getup_chnl_messages(int connfd, sqlite3 *db) {
    cJSON *j_responce = cJSON_CreateObject();

    int uid = mx_get_id_socket(db, connfd);
    char *username = mx_get_login_id(db, uid);
    char *message = get_messages(db);
    char *sender = get_sender(db);

    if (message) {
        cJSON_AddItemToObject(j_responce, "action",
                              cJSON_CreateString("getup_chnl_msgs"));
        cJSON_AddItemToObject(j_responce, "message_list",
                              cJSON_CreateString(message));
        cJSON_AddItemToObject(j_responce, "message_sender",
                              cJSON_CreateString(sender));
        cJSON_AddItemToObject(j_responce, "username",
                              cJSON_CreateString(username));
        char *jdata = cJSON_Print(j_responce);

        send_message_self(jdata, connfd);
        free(jdata);
    }
    cJSON_Delete(j_responce);

    free(message);
    free(sender);
}
