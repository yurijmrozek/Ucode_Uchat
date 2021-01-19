#include "client.h"

void mx_init_authoriz_gui(client_t *cli) {
    cli->builder = gtk_builder_new();
    gtk_builder_add_from_file(cli->builder, "client/src/gui/glade"///////////
                                            "/chat.ui", NULL);///////////////
    gtk_builder_connect_signals(cli->builder, cli);
    cli->awindow = GTK_WIDGET(gtk_builder_get_object(cli->builder,///////////
                                                     "signin_window"));////
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider,/////////////////////////////
                                    "client/src/gui/glade/style.css",
                                    NULL);///////////////////////////////////
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_signal_connect(G_OBJECT(cli->awindow),/////////////////////////////////
                                "destroy", G_CALLBACK(destroy), cli);
    gtk_widget_show_all(cli->awindow);
}
