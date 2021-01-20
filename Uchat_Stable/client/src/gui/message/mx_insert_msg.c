#include "client.h"

void mx_insert_msg(gchar *message, client_t *cli, int pos) {
    GtkListBox *msg_list = GTK_LIST_BOX(gtk_builder_get_object/////
                                        (cli->builder, "msg_list"));
    GtkStyleContext *context;
    GtkWidget *row, *hbox, *msg;

    row = gtk_list_box_row_new();
    hbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    msg = gtk_label_new(message);

    if (pos == 0) {
        context = gtk_widget_get_style_context(GTK_WIDGET(msg));
        gtk_style_context_add_class(context, "msg_intext");

        gtk_widget_set_margin_left(row, 300);
        gtk_widget_set_margin_right(msg, 50);
    }

    else if (pos == 1) {
        context = gtk_widget_get_style_context(GTK_WIDGET(msg));
        gtk_style_context_add_class(context, "msg_outext");

        gtk_widget_set_margin_right(row, 300);
        gtk_widget_set_margin_left(msg, 50);
    }

    gtk_container_add(GTK_CONTAINER(row), hbox);
    gtk_box_pack_start(GTK_BOX(hbox), msg, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(msg_list), row);
    gtk_widget_show_all(row);
    gtk_widget_show(msg);
}
