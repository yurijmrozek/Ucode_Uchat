#include "client.h"

void mx_notification_dialog(client_t *cli, char *username, char flag) {
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object
                                   (cli->builder, "user_do_dialog"));
    GtkLabel *username_lbl = GTK_LABEL(gtk_builder_get_object/////
                                       (cli->builder,/////////////
                                       "username_do_lbl_dialog"));
    GtkLabel *do_lbl = GTK_LABEL(gtk_builder_get_object///////////
                                 (cli->builder, "do_lbl_dialog"));

    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(cli->cwindow));
    
    if (flag == 'i')
        gtk_label_set_text(do_lbl, "You recieved new invite");
    else if (flag == 'a') {
        gtk_label_set_text(username_lbl, username);
        gtk_label_set_text(do_lbl, "Accept your friend invite");
    }
    else if (flag == 'd') {
        gtk_label_set_text(username_lbl, username);
        gtk_label_set_text(do_lbl, "Decline your friend invite");
    }
    else if (flag == 'r') {
        gtk_label_set_text(username_lbl, username);
        gtk_label_set_text(do_lbl, "Deleted you from friend list");
    }

    gtk_widget_show_all(dialog);

    int responce = gtk_dialog_run(GTK_DIALOG(dialog));
    if (responce == 1) {
        gtk_label_set_text(username_lbl, "");
        gtk_label_set_text(do_lbl, "");
        gtk_widget_hide(dialog);
    }
    gtk_label_set_text(username_lbl, "");
    gtk_label_set_text(do_lbl, "");
    gtk_widget_hide(dialog);
}
