#include "client.h"

void mx_init_chat_gui(client_t *cli) {
    gtk_widget_hide(cli->awindow);
    cli->cwindow = GTK_WIDGET(gtk_builder_get_object(cli->builder,///////////
                                                     "chat_window"));////////
    g_signal_connect(G_OBJECT(cli->cwindow),/////////////////////////////////
                                "destroy", G_CALLBACK(destroy), cli);
    gtk_widget_show_all(cli->cwindow);
}

/*
 *  GtkCssProvider *cssProvider = gtk_css_provider_new();
 *  gtk_css_provider_load_from_path(cssProvider,//////////////////////////////
 *                                  "client/src/gui/glade/chat/style.css",
 *                                  NULL);////////////////////////////////////
 *  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
 *                                            GTK_STYLE_PROVIDER(cssProvider),
 *                                            GTK_STYLE_PROVIDER_PRIORITY_USER);
 */
