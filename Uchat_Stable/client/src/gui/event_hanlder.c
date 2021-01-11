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

void on_lgb_btn_clicked_log(GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;

    if (mx_valid_log_creden(cli))
        mx_login_request(cli);
}
