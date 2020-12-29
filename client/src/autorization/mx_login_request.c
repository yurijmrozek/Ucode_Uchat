#include "client.h"

void mx_login_request(t_chat *chat) {
    GtkEntry *log_entry = GTK_ENTRY(gtk_builder_get_object
                                   (chat->builder, "login_username"));
    GtkEntry *pass_entry = GTK_ENTRY(gtk_builder_get_object
                                   (chat->builder, "login_password"));
    chat->username = strdup(gtk_entry_get_text(log_entry));
    for (int i = 0; chat->username[i]; i++)
        chat->username[i] = tolower(chat->username[i]);
    char *pbuffer = strdup(gtk_entry_get_text(pass_entry));
    cJSON *j_login = cJSON_CreateObject();
    cJSON_AddItemToObject(j_login, "action", cJSON_CreateString("login"));
    cJSON_AddItemToObject(j_login, "username",
                          cJSON_CreateString(chat->username));
    cJSON_AddItemToObject(j_login, "password",
                          cJSON_CreateString(pbuffer));
    char *jdata = cJSON_Print(j_login);
    write(chat->sockfd, jdata, strlen(jdata));
    gtk_entry_set_text(log_entry, "");
    gtk_entry_set_text(pass_entry, "");
    cJSON_Delete(j_login);
    free(jdata);
}
