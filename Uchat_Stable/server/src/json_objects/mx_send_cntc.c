#include "server.h"

static char *get_icon(int state) {
    if (state == 0)
        return("contact-new");
    else if (state == 1)
        return("edit-copy");
    return NULL;
}

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

static char *get_contacts(sqlite3 *db, int connfd) {
    char **cntcarr = (char **)malloc(sizeof(char *) * 10);
    char *cntc = NULL;
    int j = -1;
    sqlite3_stmt *stmt;
    int rv = 0;

    int uid = mx_get_id_socket(db, connfd);
    rv = sqlite3_prepare_v2(db, "SELECT * FROM contact WHERE ID = ?1",
                            -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, uid);
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        cntcarr[++j] = strdup(mx_get_login_id(db,
                              sqlite3_column_int64(stmt, 1)));
        cntc = strjoin(cntc, cntcarr[j]);
        cntc = strjoin(cntc, ",");
        free(cntcarr[j]);
    }
    free(cntcarr);
    return cntc;
}

static char *get_states(sqlite3 *db, int connfd) {
    char **statearr = (char **)malloc(sizeof(char *) * 10);
    char *state = NULL;
    int j = -1;
    sqlite3_stmt *stmt;
    int rv = 0;

    int uid = mx_get_id_socket(db, connfd);
    rv = sqlite3_prepare_v2(db, "SELECT * FROM contact WHERE ID = ?1",
                            -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, uid);
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        statearr[++j] = strdup(get_icon(sqlite3_column_int64(stmt, 2)));
        state = strjoin(state, statearr[j]);
        state = strjoin(state, ",");
        free(statearr[j]);
    }
    free(statearr);
    return state;
}

void mx_send_cntc(sqlite3 *db, int connfd) {
    cJSON *j_responce = cJSON_CreateObject();
    

    cJSON_AddItemToObject(j_responce, "action",
                          cJSON_CreateString("getup_cntc"));
    char *cntc = get_contacts(db, connfd);
    char *cntcstate = get_states(db, connfd);
    if (cntc) {
        cJSON_AddItemToObject(j_responce, "cntc_list",
                              cJSON_CreateString(cntc));
        cJSON_AddItemToObject(j_responce, "cntc_list_state",
                              cJSON_CreateString(cntcstate));
        char *jdata = cJSON_Print(j_responce);
        printf("\n\nTo responce:\n\n%s\n\n", jdata);
        send_message_self(jdata, connfd);
        free(jdata);
    }
    free(cntc);
    cJSON_Delete(j_responce);
}
