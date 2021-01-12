#include "client.h"

void mx_creden_accepted(client_t *cli) {
    GtkLabel *err_lbll = GTK_LABEL(gtk_builder_get_object(cli->builder,
                                                          "err_label_log"));
    GtkLabel *err_lblr = GTK_LABEL(gtk_builder_get_object(cli->builder,
                                                          "err_label_reg"));
    GtkEntry *lgn_entry_log = GTK_ENTRY(gtk_builder_get_object(cli->builder,
                                                     "lgn_entry_log"));///////
    GtkEntry *pass_entry_log = GTK_ENTRY(gtk_builder_get_object(cli->builder,
                                                      "pass_entry_log"));/////
    GtkEntry *lgn_entry_reg = GTK_ENTRY(gtk_builder_get_object(cli->builder,
                                                     "lgn_entry_reg"));///////
    GtkEntry *pass_entry_reg = GTK_ENTRY(gtk_builder_get_object(cli->builder,
                                                      "pass_entry_reg"));/////
    gtk_label_set_text(err_lbll, "");
    gtk_label_set_text(err_lblr, "");
    gtk_entry_set_text(lgn_entry_log, "");
    gtk_entry_set_text(pass_entry_log, "");
    gtk_entry_set_text(lgn_entry_reg, "");
    gtk_entry_set_text(pass_entry_reg, "");
    
    mx_init_chat_gui(cli);
}
