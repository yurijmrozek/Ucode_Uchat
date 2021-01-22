#include "client.h"

static void on_size(GtkWidget *label, GtkAllocation *alloc, gpointer data) {
    data = (void *)data;
    gtk_widget_set_size_request(label, alloc->width - 2, -1);
}

void mx_insert_msg(gchar *message, client_t *cli, int pos) {
    GtkListBox *msg_list = GTK_LIST_BOX(gtk_builder_get_object/////
                                        (cli->builder, "msg_list"));
    GtkStyleContext *context;
    GtkWidget *row, *hbox, *msg;

    row = gtk_list_box_row_new();
    hbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    msg = gtk_label_new(message);
    gtk_misc_set_alignment(GTK_MISC(msg), 0, 0.5);
    g_signal_connect(G_OBJECT(msg), "size-allocate",
                     G_CALLBACK(on_size), NULL);
    gtk_label_set_use_markup(GTK_LABEL(msg), TRUE);
    gtk_label_set_line_wrap(GTK_LABEL(msg), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(msg), PANGO_WRAP_WORD_CHAR);

    if (pos == 0) {
        context = gtk_widget_get_style_context(GTK_WIDGET(msg));
        gtk_style_context_add_class(context, "msg_intext");

        gtk_widget_set_margin_start(row, 300);
        gtk_widget_set_margin_end(msg, 10);
    }

    else if (pos == 1) {
        context = gtk_widget_get_style_context(GTK_WIDGET(msg));
        gtk_style_context_add_class(context, "msg_outext");

        gtk_widget_set_margin_end(row, 300);
        gtk_widget_set_margin_start(row, 10);
    }

    gtk_container_add(GTK_CONTAINER(row), hbox);
    gtk_box_pack_start(GTK_BOX(hbox), msg, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(msg_list), row);

    gtk_widget_show_all(row);
    gtk_widget_show(msg);
    mx_scroll_to_down(cli);
}
