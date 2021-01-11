#include "client.h"

int mx_valid_login_gui(t_chat *chat) {
    GtkEntry *log_entry = GTK_ENTRY(gtk_builder_get_object
                                   (chat->builder, "login_username"));
    GtkEntry *pass_entry = GTK_ENTRY(gtk_builder_get_object
                                   (chat->builder, "login_password"));
    GtkLabel *err_label = GTK_LABEL(gtk_builder_get_object
                                   (chat->builder, "login_err_empty"));
    char *lbuffer = (char *)gtk_entry_get_text(log_entry);
    char *pbuffer = (char *)gtk_entry_get_text(pass_entry);
    bool valid = true;

    if (strlen(lbuffer) < 6 || strlen(pbuffer) < 6)
        valid = false;
    for (int i = 0; lbuffer[i]; i++) {
        if (!isdigit(lbuffer[i]) && !isalpha(lbuffer[i])) {
            valid = false;
        }
    }
    if (!valid) {
        printf("login type valid error\n");
        gtk_label_set_text (err_label,
                            "Invalid login or pass type: [abc123][6ch min]\n");
        return 2;
    }
    gtk_label_set_text(err_label, "");
    return 1;
}
