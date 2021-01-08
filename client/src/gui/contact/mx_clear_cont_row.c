#include "client.h"

void mx_clear_cont_row(t_chat *chat) {
    GtkListBox *cont_list = GTK_LIST_BOX(gtk_builder_get_object(chat->builder,
                                         "contact_list"));
    GtkListBoxRow *row; 

    if ((row = gtk_list_box_get_row_at_index(cont_list, 0))) {
        while (row) {
            gtk_widget_destroy(GTK_WIDGET(row));
            row = gtk_list_box_get_row_at_index(cont_list, 0);
        }
    }
}
