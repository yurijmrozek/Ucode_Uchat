#include "client.h"

void mx_scroll_to_down(client_t *cli) {
    GtkAdjustment *vertical_adjust;
    GtkScrolledWindow *scrolled_win = GTK_SCROLLED_WINDOW
                                       (gtk_builder_get_object
                                       (cli->builder, "msg_scrolled_window"));
    vertical_adjust = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW
                                                          (scrolled_win));
    gtk_adjustment_set_value(vertical_adjust, gtk_adjustment_get_upper///
                             (vertical_adjust));/////////////////////////
    gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(scrolled_win),
                                        vertical_adjust);////////////////
}
