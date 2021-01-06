#include "client.h"

void mx_addcont_handl_res(cJSON *j_responce, t_chat *chat) {
    GtkLabel *err_label = GTK_LABEL(gtk_builder_get_object
                                       (chat->builder, "contact_lbl_err"));
    cJSON *j_valid = cJSON_GetObjectItemCaseSensitive(j_responce, "valid");
    cJSON *j_login = cJSON_GetObjectItemCaseSensitive(j_responce, "login");

    char *valid = strdup(j_valid->valuestring);
    char *login = strdup(j_login->valuestring);
    if (!strcmp(valid, "true")) {
        gtk_label_set_text(err_label, "");
        mx_create_contact(chat, login);
    }
    if (!strcmp(valid, "false")) {
        gtk_label_set_text(err_label, "Invalid user!");
    }
    if (!strcmp(valid, "exist")) {
        gtk_label_set_text(err_label, "User exist!");
    }
}
