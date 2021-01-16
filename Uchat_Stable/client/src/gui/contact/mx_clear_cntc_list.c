#include "client.h"

static void clear_cntc_outgoin_list(client_t *cli) {
    GtkListBox *incoming_list = GTK_LIST_BOX(gtk_builder_get_object
                                             (cli->builder,
                                             "cntc_incoming_list"));
    GtkListBoxRow *row;

    if ((row = gtk_list_box_get_row_at_index(incoming_list, 0))) {
        while (row) {
            gtk_widget_destroy(GTK_WIDGET(row));
            row = gtk_list_box_get_row_at_index(incoming_list, 0);
        }
    }
}

static void clear_cntc_incoming_list(client_t *cli) {
    GtkListBox *outgoing_list = GTK_LIST_BOX(gtk_builder_get_object
                                             (cli->builder,
                                             "cntc_outgoing_list"));
    GtkListBoxRow *row;

    if ((row = gtk_list_box_get_row_at_index(outgoing_list, 0))) {
        while (row) {
            gtk_widget_destroy(GTK_WIDGET(row));
            row = gtk_list_box_get_row_at_index(outgoing_list, 0);
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
    clear_cntc_incoming_list(cli);
    clear_cntc_outgoin_list(cli);
}
