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
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider,/////////////////////////////
                                    "client/src/gui/glade/standart.css",
                                    NULL);///////////////////////////////////
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
}
