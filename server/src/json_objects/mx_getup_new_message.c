#include "server.h"

static char *strnew(const int size) {
    char *strnew = malloc(size < 0 ? size : size + 1);

    for (int i = 0; strnew[i] && i <= size; ++i)
        strnew[i] = '\0';
    return strnew; 
}

static int count_words(const char *str, char delimiter) {
    int counter = 0;
    for (;*str; ++str) {
        if (*str != delimiter && ++counter)
            for (;*(str + 1) && *str != delimiter; ++str);
    }
    return counter;
}

static char **strsplit(const char *s, char c) {
    int xcount_words = 0;
    if (!s || (xcount_words = count_words(s, c)) < 0)
        return NULL;
    char **split = malloc(sizeof(char*) * xcount_words + 1);
    split[xcount_words] = NULL;
    for (int i = 0, len = 0; i < xcount_words; ++i, s += len, len = 0) {
        for (; *s == c; ++s);
        for (; s[len] != c; ++len);
        split[i] = strnew(len);
        strncpy(split[i], s, len);
    }
    return split;
}

void mx_getup_new_message(int uid, char *message, char *username, 
                          int sockfd, sqlite3 *db, char *state) {
    char *sender = mx_get_login_id(db, uid);
    int cid = mx_get_id_login(db, username);

    char *msgid = mx_return_id_msg(db, uid, cid, message);
    char **id = strsplit(msgid, ',');

    int i = 0;

    while(id[i]) {
        i++;
    }

    cJSON *j_responce = cJSON_CreateObject();
    cJSON_AddItemToObject(j_responce, "action",
                          cJSON_CreateString("getup_new_msg"));
    cJSON_AddItemToObject(j_responce, "message_list",
                          cJSON_CreateString(message));
    cJSON_AddItemToObject(j_responce, "message_sender",
                          cJSON_CreateString(sender));
    cJSON_AddItemToObject(j_responce, "username",
                          cJSON_CreateString(username));
    cJSON_AddItemToObject(j_responce, "state", cJSON_CreateString(state));
    cJSON_AddItemToObject(j_responce, "msgid", cJSON_CreateString(id[i - 1]));
    char *jdata = cJSON_Print(j_responce);

    send_message_self(jdata, sockfd);
    free(msgid);
    free(jdata);
    free(sender);
    cJSON_Delete(j_responce);
}
