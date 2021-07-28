#include "client.h"

void mx_clear_msg_list(client_t *cli) {
    GtkListBox *msg_list = GTK_LIST_BOX(gtk_builder_get_object(cli->builder,
                                                               "msg_list"));
    GtkListBoxRow *row;

    if ((row = gtk_list_box_get_row_at_index(msg_list, 0))) {
        while (row) {
            gtk_widget_destroy(GTK_WIDGET(row));
            row = gtk_list_box_get_row_at_index(msg_list, 0);
        }
    }
}
