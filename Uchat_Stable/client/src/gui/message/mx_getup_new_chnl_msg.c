#include "client.h"

void mx_getup_new_chnl_msg(cJSON *j_responce, client_t *cli) {
    int pos = 1;
    bool valid = false;

    GtkLabel *current_user_lbl = GTK_LABEL(gtk_builder_get_object
                                           (cli->builder, "current_user_lbl"));
    cJSON *j_msg = cJSON_GetObjectItemCaseSensitive(j_responce, "message_list");
    cJSON *j_msg_sender = cJSON_GetObjectItemCaseSensitive(j_responce,///////
                                                           "message_sender");
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_responce,
                                                         "username");
    char *cur_uslbl = strdup(gtk_label_get_text(current_user_lbl));

    if (!strcmp(cur_uslbl, "#Paradise"))
        valid = true;
    if (!strcmp(j_msg_sender->valuestring, j_username->valuestring))
        pos = 0;
    if (valid)
        mx_insert_chnl_msg(j_msg_sender->valuestring,
                           j_msg->valuestring, cli, pos);
    free(cur_uslbl);
}
