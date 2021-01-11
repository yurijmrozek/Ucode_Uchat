#include "client.h"

void mx_valid_csearch(t_chat *chat) {
    GtkLabel *err_label = GTK_LABEL(gtk_builder_get_object
                                   (chat->builder, "contact_lbl_err"));
    GtkEntry *log_entry = GTK_ENTRY(gtk_builder_get_object
                                   (chat->builder, "contact_entry_search"));
    char *lbuffer = (char *)gtk_entry_get_text(log_entry);
    if (strlen(lbuffer) < 6) {
        gtk_label_set_text(err_label, "[abc123][6ch min]");
        return;
    }
    for (int i = 0; lbuffer[i]; i++) {
        if (!isalpha(lbuffer[i]) && !isdigit(lbuffer[i])) {
            gtk_label_set_text(err_label, "[abc123][6ch min]");
            return;
        }
    }
    for (int i = 0; lbuffer[i]; i++)
        lbuffer[i] = tolower(lbuffer[i]);
    cJSON *j_addc = cJSON_CreateObject();
    cJSON_AddItemToObject(j_addc, "action", cJSON_CreateString("add_cont"));
    cJSON_AddItemToObject(j_addc, "login",
                          cJSON_CreateString(lbuffer));
    char *jdata = cJSON_Print(j_addc);
    write(chat->sockfd, jdata, strlen(jdata));
    gtk_entry_set_text(log_entry, "");
    cJSON_Delete(j_addc);
    free(jdata);
}
