#include "client.h"

void mx_init_gui(t_chat *chat) {
    gtk_init(NULL, NULL);
    GError* error = NULL;

    chat->builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(chat->builder, "client/src/gui/glade/"
                                             "chat.ui", &error)) {
        g_critical("error load file: %s", error->message);
        g_error_free(error);
        gtk_main_quit();
    }
    gtk_builder_connect_signals(chat->builder, chat);
    chat->window = GTK_WIDGET(gtk_builder_get_object(chat->builder, "window"));
    if (!chat->window) {
        g_critical("error getting window");
        gtk_main_quit();
    }
    g_signal_connect(G_OBJECT(chat->window),
                                "destroy", G_CALLBACK(destroy), chat);
}
