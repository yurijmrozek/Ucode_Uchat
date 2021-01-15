#include "client.h"

static void clear_inv_list(client_t *cli) {
    GtkListBox *inv_list = GTK_LIST_BOX(gtk_builder_get_object(cli->builder,
                                                                "inv_list"));
    GtkListBoxRow *row;

    if ((row = gtk_list_box_get_row_at_index(inv_list, 0))) {
        while (row) {
            gtk_widget_destroy(GTK_WIDGET(row));
            row = gtk_list_box_get_row_at_index(inv_list, 0);
        }
    }
}

void mx_clear_cntc_list(client_t *cli) {
    GtkListBox *cntc_list = GTK_LIST_BOX(gtk_builder_get_object(cli->builder,
                                                                "cntc_list"));
    GtkListBoxRow *row;

    if ((row = gtk_list_box_get_row_at_index(cntc_list, 0))) {
        while (row) {
            gtk_widget_destroy(GTK_WIDGET(row));
            row = gtk_list_box_get_row_at_index(cntc_list, 0);
        }
    }
    clear_inv_list(cli);
}
