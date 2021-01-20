#include "client.h"

void mx_clear_chat(client_t *cli) {
    mx_clear_cntc_list(cli);
    mx_clear_msg_list(cli);
    GtkLabel *current_user = GTK_LABEL(gtk_builder_get_object
                                       (cli->builder, "current_user_lbl"));
    gtk_label_set_text(current_user, "Select contact to start chatting");
    GtkTextView *entry = GTK_TEXT_VIEW(gtk_builder_get_object///////////
                                   (cli->builder,///////////////////////
                                   "msg_entry"));

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(entry);
    gtk_text_buffer_set_text(buffer, "", 1);
}
