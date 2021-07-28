#include "client.h"

void mx_sending_invite_dialog(client_t *cli, char valid) {
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object
                                   (cli->builder, "invite_dialog"));
    GtkLabel *err_label = GTK_LABEL(gtk_builder_get_object/////
                                    (cli->builder, "err_lbl"));
    GtkLabel *succ_label = GTK_LABEL(gtk_builder_get_object/////
                                    (cli->builder, "succ_lbl"));

    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(cli->cwindow));
    if (valid == 't')
        gtk_label_set_text(succ_label, "Invite sended");
    else if (valid == 'i')
        gtk_label_set_text(err_label, "    Invalid syntax\n[abc123][6ch min]");
    else if (valid == 'm')
        gtk_label_set_text(err_label, "\tInvalid syntax\n "
                                      "[6ch min - 255ch max]");
    else if (valid == 'e')
        gtk_label_set_text(err_label, " User already\nin contact list");
    else if (valid == 'u')
        gtk_label_set_text(err_label, "User undefined");
    else if (valid == 'f')
        gtk_label_set_text(err_label, "Invite already exist ");
    else if (valid == 'c')
        gtk_label_set_text(err_label, "First, choose contact"
                                      "\n   to start chatting");
    else if (valid == '~')
        gtk_label_set_text(err_label, "~^~ Please dont ~^~  "  \
                                      "\n  use this [~ ^] chars  ");
    else if (valid == 'd')
        gtk_label_set_text(err_label, "  You can delete \nonly your message");
    else if (valid == '6')
        gtk_label_set_text(err_label, "SHIZA?)?)?)");
    gtk_widget_show_all(dialog);

    int responce = gtk_dialog_run(GTK_DIALOG(dialog));
    if (responce == 1) {
        gtk_label_set_text(err_label, "");
        gtk_label_set_text(succ_label, "");
        gtk_widget_hide(dialog);
    }
    gtk_label_set_text(err_label, "");
    gtk_label_set_text(succ_label, "");
    gtk_widget_hide(dialog);
}
