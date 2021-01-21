#include "client.h"

void mx_getup_new_msg(cJSON *j_responce, client_t *cli) {
    bool valid = false;
    int pos = 0;

    GtkLabel *current_user_lbl = GTK_LABEL(gtk_builder_get_object
                                           (cli->builder, "current_user_lbl"));
    cJSON *j_msg = cJSON_GetObjectItemCaseSensitive(j_responce, "message_list");
    cJSON *j_msg_sender = cJSON_GetObjectItemCaseSensitive(j_responce,///////
                                                           "message_sender");
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_responce,
                                                         "username");
    char *cur_uslbl = strdup(gtk_label_get_text(current_user_lbl));

    if (!strcmp(j_msg_sender->valuestring, cur_uslbl)) {
        valid = true;
    }
    if (!strcmp(j_msg_sender->valuestring, cur_uslbl))
        pos = 1;
    if (valid)
        mx_insert_msg(j_msg->valuestring, cli, pos);
}
