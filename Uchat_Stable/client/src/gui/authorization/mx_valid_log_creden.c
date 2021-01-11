#include "client.h"

bool mx_valid_log_creden(client_t *cli) {
    GtkEntry *log_entry = GTK_ENTRY(gtk_builder_get_object
                                   (cli->builder, "lgn_entry_log"));
    GtkEntry *pass_entry = GTK_ENTRY(gtk_builder_get_object//////////
                                   (cli->builder, "pass_entry_log"));
    GtkLabel *err_label = GTK_LABEL(gtk_builder_get_object///////////
                                   (cli->builder, "err_label_log"));
    char *lbuffer = strdup(gtk_entry_get_text(log_entry));
    char *pbuffer = strdup(gtk_entry_get_text(pass_entry));
    bool valid = true;

    if (strlen(lbuffer) < 6 || strlen(pbuffer) < 6)
        valid = false;
    for (int i = 0; lbuffer[i]; i++) {
        if (!isdigit(lbuffer[i]) && !isalpha(lbuffer[i])) {
            valid = false;
        }
    }
    free(lbuffer);
    free(pbuffer);
    if (!valid) {
        gtk_label_set_text (err_label,////////////////////////////////////////
                            "Invalid syntax [abc123][6ch min]\n");///////////
        return false;
    }
    gtk_label_set_text(err_label, "");
    return true;
}
