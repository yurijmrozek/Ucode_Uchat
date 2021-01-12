#include "client.h"

void destroy(client_t *cli) {
    close(cli->sockfd);
    gtk_main_quit();
}

void on_reg_btn_clicked_log(GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;
    GtkStack *stk = GTK_STACK(gtk_builder_get_object///////////////////
                              (cli->builder, "authoriz_stack"));
    GtkEntry *log_entry = GTK_ENTRY(gtk_builder_get_object/////////////
                                    (cli->builder, "lgn_entry_log"));
    GtkEntry *pass_entry = GTK_ENTRY(gtk_builder_get_object////////////
                                    (cli->builder, "pass_entry_log"));
    GtkLabel *err_label = GTK_LABEL(gtk_builder_get_object/////////////
                                    (cli->builder, "err_label_log"));
    gtk_label_set_text(err_label, "");
    gtk_entry_set_text(log_entry, "");
    gtk_entry_set_text(pass_entry, "");
    gtk_stack_set_visible_child_name(stk, "register_page");
}

void on_back_btn_clicked_reg(GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;
    GtkStack *stk = GTK_STACK(gtk_builder_get_object///////////////////
                              (cli->builder, "authoriz_stack"));
    GtkEntry *log_entry = GTK_ENTRY(gtk_builder_get_object/////////////
                                    (cli->builder, "lgn_entry_reg"));
    GtkEntry *pass_entry = GTK_ENTRY(gtk_builder_get_object////////////
                                    (cli->builder, "pass_entry_reg"));
    GtkLabel *err_label = GTK_LABEL(gtk_builder_get_object/////////////
                                    (cli->builder, "err_label_reg"));
    gtk_label_set_text(err_label, "");
    gtk_entry_set_text(log_entry, "");
    gtk_entry_set_text(pass_entry, "");
    gtk_stack_set_visible_child_name(stk, "login_page");
}

void on_reg_btn_clicked_reg(GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;

    if (mx_valid_reg_creden(cli))
        mx_register_request(cli);
}

void on_lgn_btn_clicked_log(GtkWidget *button, gpointer data) {
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
    // mx_clear_chat();
    gtk_widget_hide(cli->cwindow);
    gtk_widget_show(cli->awindow);
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
        if (!valid) {
            printf("false\n");
            mx_sending_invite_dialog(cli, 'i');
        }
        free(username);
        gtk_entry_set_text(log_entry, "");
        gtk_widget_hide(dialog);
    }
    else {
        gtk_entry_set_text(log_entry, "");
        gtk_widget_hide(dialog);
    }
}
