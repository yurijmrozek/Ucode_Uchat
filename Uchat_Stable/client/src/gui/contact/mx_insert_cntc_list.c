#include "client.h"

void mx_insert_cntc_list(char *username, client_t *cli, char *icon) {
    if (!strcmp(icon, "document-revert-symbolic")) {
        GtkListBox *notf_note_list = GTK_LIST_BOX(gtk_builder_get_object
                                                  (cli->builder,////////
                                                  "cntc_incoming_list"));
        GtkWidget *row, *hbox, *lgn, *img;

        GtkIconSize size = gtk_icon_size_register(NULL, 10, 10);

        row = gtk_list_box_row_new();
        hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

        lgn = gtk_label_new(username);
        img = gtk_image_new_from_icon_name((icon), size);

        gtk_container_add(GTK_CONTAINER(row), hbox);
        gtk_box_pack_start(GTK_BOX(hbox), img, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(hbox), lgn, FALSE, FALSE, 0);
        gtk_widget_set_size_request(img, 35, 35);

        gtk_list_box_insert(notf_note_list, row, 0);
        gtk_widget_show_all(row);
        gtk_widget_show(lgn);
        gtk_widget_show(img);
    }

    else if (!strcmp(icon, "contact-new")) {
        GtkListBox *inv_list = GTK_LIST_BOX(gtk_builder_get_object
                                            (cli->builder,////////
                                            "cntc_outgoing_list"));
        GtkWidget *row, *hbox, *lgn, *img;

        GtkIconSize size = gtk_icon_size_register(NULL, 10, 10);

        row = gtk_list_box_row_new();
        hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

        lgn = gtk_label_new(username);
        img = gtk_image_new_from_icon_name((icon), size);

        gtk_container_add(GTK_CONTAINER(row), hbox);
        gtk_box_pack_start(GTK_BOX(hbox), img, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(hbox), lgn, FALSE, FALSE, 0);
        gtk_widget_set_size_request(img, 35, 35);

        gtk_list_box_insert(inv_list, row, 0);
        gtk_widget_show_all(row);
        gtk_widget_show(lgn);
        gtk_widget_show(img);
    }

    else if (!strcmp(icon, "edit-copy")) {
        GtkListBox *cntc_list = GTK_LIST_BOX(gtk_builder_get_object/////
                                            (cli->builder, "cntc_list"));
        GtkWidget *row, *hbox, *lgn, *img;

        GtkIconSize size = gtk_icon_size_register(NULL, 10, 10);

        row = gtk_list_box_row_new();
        hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

        lgn = gtk_label_new(username);
        img = gtk_image_new_from_icon_name((icon), size);

        gtk_container_add(GTK_CONTAINER(row), hbox);
        gtk_box_pack_start(GTK_BOX(hbox), img, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(hbox), lgn, FALSE, FALSE, 0);
        gtk_widget_set_size_request(img, 35, 35);


        gtk_list_box_insert(cntc_list, row, 0);
        gtk_widget_show_all(row);
        gtk_widget_show(lgn);
        gtk_widget_show(img);
    }
}
