#include "client.h"

void mx_login_responce(cJSON *j_responce, client_t *cli) {
    cJSON *j_valid = cJSON_GetObjectItemCaseSensitive(j_responce, "valid");
    cJSON *j_reason = cJSON_GetObjectItemCaseSensitive(j_responce, "reason");
    GtkLabel *err_label = GTK_LABEL(gtk_builder_get_object(cli->builder,
                                                           "err_lbl_log"));
    if (!strcmp(j_valid->valuestring, "true")
        && !strcmp(j_reason->valuestring, "true_credentials"))
        mx_creden_accepted(cli);
    else if (!strcmp(j_valid->valuestring, "false")) {
        if (!strcmp(j_reason->valuestring, "user_already_online"))
            gtk_label_set_text(err_label, "User already online");
        else if (!strcmp(j_reason->valuestring, "invalid_credentials_given"))
            gtk_label_set_text(err_label, "Invalid credentials given");
    }
}
