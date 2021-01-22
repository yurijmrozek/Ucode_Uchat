#include "client.h"

void mx_register_request(client_t *cli) {
    GtkEntry *log_entry = GTK_ENTRY(gtk_builder_get_object//////////
                                    (cli->builder, "username_log"));
    GtkEntry *pass_entry = GTK_ENTRY(gtk_builder_get_object//////////
                                    (cli->builder, "password_log"));
    char *username = strdup(gtk_entry_get_text(log_entry));
    char *password = strdup(gtk_entry_get_text(pass_entry));
    char *hashpass = g_compute_checksum_for_string(G_CHECKSUM_SHA256, password,
                                                   strlen(password));
    for (int i = 0; username[i]; i++)
        username[i] = tolower(username[i]);
    cJSON *j_request = cJSON_CreateObject();
    cJSON_AddItemToObject(j_request, "action",//////////////
                          cJSON_CreateString("signup_user"));
    cJSON_AddItemToObject(j_request, "username",//////////////
                          cJSON_CreateString(username));
    cJSON_AddItemToObject(j_request, "password",//////////////
                          cJSON_CreateString(hashpass));
    char *jdata = cJSON_Print(j_request);
    send_message_self(jdata, cli->sockfd);
    gtk_entry_set_text(log_entry, "");
    gtk_entry_set_text(pass_entry, "");
    free(jdata);
    free(username);
    free(password);
    g_free(hashpass);
    cJSON_Delete(j_request);
}
