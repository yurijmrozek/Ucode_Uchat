#include "server.h"

static char *strnew(const int size) {
    char *strnew = malloc(size < 0 ? size : size + 1);

    for (int i = 0; strnew && i <= size; ++i)
        strnew[i] = '\0';
    return strnew;
}

static char *strjoin(char const *s1, char const *s2) {
    char *result = NULL;

    if (!s1 && !s2)
        return NULL;
    if (!s1)
        return strdup(s2);
    if (!s2)
        return strdup(s1);

    result = strnew(strlen(s1) + strlen(s2));
    strcpy(result, s1);
    result = strcat(result, s2);
    return result;
}

static char *get_contacts(t_database *t_db, int socket1) {
    char **contarr = (char **)malloc(sizeof(char *) * 10);
    char *contacts = NULL;
    int j = -1;
    sqlite3_stmt *stmt;
    gint32 rv = 0;
    
    int uid = mx_get_id_socket(t_db, socket1);
    rv = sqlite3_prepare_v2(t_db->db, "SELECT * FROM contact WHERE ID = ?1",
                            -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, uid);
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        contarr[++j] = strdup(mx_get_login_id(t_db,
                               sqlite3_column_int64(stmt, 1)));
        printf("contarr[%d]: %s\n", j, contarr[j]);
        contacts = strjoin(contacts, contarr[j]);
        contacts = strjoin(contacts, ",");
        contarr[j] = NULL;
    }
    free(contarr);
    printf("contact: %s\n", contacts);
    return contacts;
}

void mx_send_contacts(t_database *t_db, int socket1) {
    cJSON *j_responce = cJSON_CreateObject();

    cJSON_AddItemToObject(j_responce, "action",
                          cJSON_CreateString("getup_contact"));
    char *contacts = get_contacts(t_db, socket1);
    if (contacts)
        cJSON_AddItemToObject(j_responce, "contacts",
                              cJSON_CreateString(contacts));
    char *jdata = cJSON_Print(j_responce);
    printf("\n\nTo responce:\n\n%s\n\n", jdata);
    write(socket1, jdata, strlen(jdata));
    cJSON_Delete(j_responce);
    free(jdata);
    free(contacts);
}
