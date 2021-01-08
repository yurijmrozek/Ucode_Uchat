#include "client.h"

void mx_create_contact(t_chat *chat, char *login) {
    usleep(100);

    GtkListBox *cont_list = GTK_LIST_BOX
                            (gtk_builder_get_object(chat->builder,
                                                    "contact_list"));
    GtkWidget *label1;
    if ((label1 = gtk_label_new(login))) {
        gtk_container_add(GTK_CONTAINER(cont_list), label1);
        g_idle_add ((int (*)(void *))mx_show_widget, cont_list);
    }
}
