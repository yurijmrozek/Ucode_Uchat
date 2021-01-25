#include "client.h"

void mx_scroll_to_down(client_t *cli) {
    GtkScrolledWindow *scrolled_win = GTK_SCROLLED_WINDOW
                                       (gtk_builder_get_object
                                       (cli->builder, "msg_scrolled_window"));
    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment
                         (GTK_SCROLLED_WINDOW(scrolled_win));
    double value = gtk_adjustment_get_upper(adj);

    gtk_adjustment_set_value(adj, value);
}
