#include "client.h"

void mx_create_contact(t_chat *chat, char *login) {
    GtkListBox *cont_list = GTK_LIST_BOX
                            (gtk_builder_get_object(chat->builder,
                                                    "contact_list"));
    GtkWidget *label1, *label2, *hbox;
    chat->cont_row = gtk_list_box_row_new();
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    label1 = gtk_label_new(login);
    label2 = gtk_label_new("Hello");

    gtk_container_add(GTK_CONTAINER(chat->cont_row), hbox);
    gtk_box_pack_start(GTK_BOX(hbox), label1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), label2, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(cont_list), chat->cont_row);
    gtk_widget_show_all(chat->window);
}
