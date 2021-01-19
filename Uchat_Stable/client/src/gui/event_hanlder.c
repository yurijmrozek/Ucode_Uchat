#include "client.h"

void destroy(client_t *cli) {
    close(cli->sockfd);
    gtk_main_quit();
}

void on_signup_btn_log_clicked(GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;

    if (mx_valid_log_creden(cli))
        mx_register_request(cli);
}

void on_signin_btn_log_clicked(GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;

    if (mx_valid_log_creden(cli))
        mx_login_request(cli);
}

void on_log_out_btn_clicked(GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;
    cJSON *j_request = cJSON_CreateObject();
    
    cJSON_AddItemToObject(j_request, "action",//////////////
                          cJSON_CreateString("logout_user"));
    char *jdata = cJSON_Print(j_request);
    
    send_message_self(jdata, cli->sockfd);
    free(jdata);
    cJSON_Delete(j_request);
    mx_clear_chat(cli);
    gtk_widget_hide(cli->cwindow);
    gtk_widget_show(cli->awindow);
}

// void on_cntc_list_row_selected(GtkWidget *button, gpointer data) {
//     client_t *cli = (client_t *)data;
//     GtkListBox *cntc_list = GTK_LIST_BOX(gtk_builder_get_object/////////
//                                          (cli->builder, "cntc_list"));
//     GtkListBoxRow *row = gtk_list_box_get_selected_row(cntc_list);
//     if (row) {
//         GList *gl_row = gtk_container_get_children(GTK_CONTAINER(row));
//         GList *gl_box = gtk_container_get_children(GTK_CONTAINER(gl_row->data));
//         GtkLabel *lbl = GTK_LABEL(gl_box->next->data);
//         char *login = (char *)gtk_label_get_text(lbl);
        
//         printf("%s\n", login);
//     }
// }

void on_cntc_incoming_allow_btn_clicked(GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;
    GtkListBox *cntc_list = GTK_LIST_BOX(gtk_builder_get_object/////////
                                         (cli->builder, "cntc_incoming_list"));
    GtkListBoxRow *row = gtk_list_box_get_selected_row(cntc_list);
    if (row) {
        GList *gl_row = gtk_container_get_children(GTK_CONTAINER(row));
        GList *gl_box = gtk_container_get_children(GTK_CONTAINER(gl_row->data));
        GtkLabel *lbl = GTK_LABEL(gl_box->next->data);
        char *login = (char *)gtk_label_get_text(lbl);
        
        mx_accept_cntc_request(cli, login);
    }
}

void on_cntc_incoming_decline_btn_clicked(GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;
    GtkListBox *cntc_list = GTK_LIST_BOX(gtk_builder_get_object/////////
                                         (cli->builder, "cntc_incoming_list"));
    GtkListBoxRow *row = gtk_list_box_get_selected_row(cntc_list);
    if (row) {
        GList *gl_row = gtk_container_get_children(GTK_CONTAINER(row));
        GList *gl_box = gtk_container_get_children(GTK_CONTAINER(gl_row->data));
        GtkLabel *lbl = GTK_LABEL(gl_box->next->data);
        char *login = (char *)gtk_label_get_text(lbl);
        
        mx_decline_cntc_request(cli, login);
    }
}

void on_cntc_outgoing_remove_btn_clicked(GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;
    GtkListBox *cntc_list = GTK_LIST_BOX(gtk_builder_get_object/////////
                                         (cli->builder, "cntc_outgoing_list"));
    GtkListBoxRow *row = gtk_list_box_get_selected_row(cntc_list);
    if (row) {
        GList *gl_row = gtk_container_get_children(GTK_CONTAINER(row));
        GList *gl_box = gtk_container_get_children(GTK_CONTAINER(gl_row->data));
        GtkLabel *lbl = GTK_LABEL(gl_box->next->data);
        char *login = (char *)gtk_label_get_text(lbl);
        
        mx_remove_cntc_request(cli, login, "outgoing_list");
    }
}

void on_cntc_remove_btn_clicked(GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;
    GtkListBox *cntc_list = GTK_LIST_BOX(gtk_builder_get_object/////////
                                         (cli->builder, "cntc_list"));
    GtkWidget *lgnlbl = GTK_WIDGET(gtk_builder_get_object///////////////
                                   (cli->builder,///////////////////////
                                   "remove_cntc_dialog_lgn_label"));
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object///////////////
                                   (cli->builder, "remove_cntc_dialog"));
    GtkListBoxRow *row = gtk_list_box_get_selected_row(cntc_list);
    if (row) {
        GList *gl_row = gtk_container_get_children(GTK_CONTAINER(row));
        GList *gl_box = gtk_container_get_children(GTK_CONTAINER(gl_row->data));
        GtkLabel *lbl = GTK_LABEL(gl_box->next->data);
        char *login = (char *)gtk_label_get_text(lbl);
        gtk_label_set_text(GTK_LABEL(lgnlbl), login);

        gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(cli->cwindow));
        gtk_widget_show_all(dialog);

        int responce = gtk_dialog_run(GTK_DIALOG(dialog));
        if (responce == 1) {
            gtk_label_set_text(GTK_LABEL(lgnlbl), "");
            gtk_widget_hide(dialog);
            mx_remove_cntc_request(cli, login, "cntc_list");
        }
        else {
            gtk_label_set_text(GTK_LABEL(lgnlbl), "");
            gtk_widget_hide(dialog);
        }
    }
}

void on_cntc_add_btn_clicked(GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;
    char *username;
    bool valid = true;

    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                          "cntc_add_dialog"));
    GtkEntry *log_entry = GTK_ENTRY(gtk_builder_get_object////////
                                    (cli->builder,////////////////
                                    "cntc_dialog_username_entry"));
    
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(cli->cwindow));
    gtk_widget_show_all(dialog);

    int responce = gtk_dialog_run(GTK_DIALOG(dialog));
    if (responce == 1) {
        valid = true;
        username = strdup(gtk_entry_get_text(log_entry));
        for (int i = 0; username[i]; i++) {
            if (!isalpha(username[i]) && !isdigit(username[i]))
                valid = false;
        }
        if (strlen(username) < 6) {
                valid = false;
        }
        if (valid)
            mx_add_cntc_request(cli, username);
        if (!valid)
            mx_sending_invite_dialog(cli, 'i');
        free(username);
        gtk_entry_set_text(log_entry, "");
        gtk_widget_hide(dialog);
    }
    else {
        gtk_entry_set_text(log_entry, "");
        gtk_widget_hide(dialog);
    }
}
