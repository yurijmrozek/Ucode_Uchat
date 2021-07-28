#include "client.h"

void mx_register_responce(cJSON *j_responce, client_t *cli) {
    cJSON *j_valid = cJSON_GetObjectItemCaseSensitive(j_responce, "valid");
    cJSON *j_reason = cJSON_GetObjectItemCaseSensitive(j_responce, "reason");
    GtkLabel *err_label = GTK_LABEL(gtk_builder_get_object(cli->builder,
                                                           "err_lbl_log"));
    
    if (!strcmp(j_valid->valuestring, "false")) {
        if (!strcmp(j_reason->valuestring, "user_exist"))
            gtk_label_set_text(err_label, "This login was already exist");
    }
}
