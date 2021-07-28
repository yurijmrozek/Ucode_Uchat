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

char *mx_return_id_msg(sqlite3 *db, int uid, int cid, char *message) {
    char **idarr = (char **)malloc(sizeof(char *) * 10);
    char *id = NULL;
    int j = -1;
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v2(db, "SELECT * FROM message WHERE ID = ?1 "  \
                                "AND CONT = ?2 AND MESSAGE = ?3",
                            -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, uid);
    sqlite3_bind_int(stmt, 2, cid);
    sqlite3_bind_text(stmt, 3, message, -1, SQLITE_STATIC);
    
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        idarr[++j] = strdup((char *)sqlite3_column_text(stmt, 3));
        id = strjoin(id, idarr[j]);
        id = strjoin(id, ",");
    }
    free(idarr);
    return id;
}
