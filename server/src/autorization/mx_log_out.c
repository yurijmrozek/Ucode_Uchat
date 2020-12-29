#include "server.h"

void mx_log_out(t_server *server, int socket1) {
    cJSON *j_responce = cJSON_CreateObject();
    cJSON_AddItemToObject(j_responce, "action", cJSON_CreateString("log_out"));
    cJSON_AddItemToObject(j_responce, "valid",
                          cJSON_CreateString("true"));
    char *jdata = cJSON_Print(j_responce);
    printf("\n\nTo responce:\n\n%s\n\n", jdata);
    mx_clean_socket_db(server->t_db, socket1);
    write(socket1, jdata, strlen(jdata));
    cJSON_Delete(j_responce);
    free(jdata);
}
