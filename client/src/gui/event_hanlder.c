#include "client.h"

void destroy(client_t *cli) {
    close(cli->sockfd);
    gtk_main_quit();
}

void on_signup_btn_log_clicked(__attribute__((unused)) GtkWidget *button,
                               gpointer data) {
    client_t *cli = (client_t *)data;

    if (mx_valid_log_creden(cli))
        mx_register_request(cli);
}

void on_signin_btn_log_clicked(__attribute__((unused))GtkWidget *button,
                               gpointer data) {
    client_t *cli = (client_t *)data;

    if (mx_valid_log_creden(cli))
        mx_login_request(cli);
}

void on_log_out_btn_clicked(__attribute__((unused)) GtkWidget *button,
                            gpointer data) {
    client_t *cli = (client_t *)data;
    cJSON *j_request = cJSON_CreateObject();

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider,
                                    "client/src/gui/glade/style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_image_set_from_file (GTK_IMAGE(gtk_builder_get_object(cli->builder,
                             "set_img")),
                             "client/src/gui/glade/assets/settings.png");                                           
    gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(cli->builder,
                            "cntc_invader")),
                            "client/src/gui/glade/assets/invader.png");

    cJSON_AddItemToObject(j_request, "action",//////////////
                          cJSON_CreateString("logout_user"));
    char *jdata = cJSON_Print(j_request);
    
    cli->set_window = GTK_WIDGET(gtk_builder_get_object(cli->builder,///////
                                                     "set_window"));////////
    g_signal_connect(G_OBJECT(cli->builder),////////////////////////////////
                                "clicked", G_CALLBACK(destroy), cli);

    send_message_self(jdata, cli->sockfd);
    free(jdata);
    cJSON_Delete(j_request);
    mx_clear_chat(cli);
    gtk_widget_hide(cli->cwindow);
    gtk_widget_hide(cli->set_window);
    gtk_widget_show(cli->awindow);
}

void on_clicked_settings(__attribute__((unused))GtkWidget *button, void *data) {
    client_t *cli = (client_t *)data;

    cli->set_window = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                        "set_window"));
    gtk_widget_show_all(cli->set_window); 
    cli->set_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);                                         
}

void on_back_to_chat(__attribute__((unused)) GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;

    cli->set_window = GTK_WIDGET(gtk_builder_get_object(cli->builder,///////
                                                     "set_window"));////////
    g_signal_connect(G_OBJECT(cli->builder),////////////////////////////////
                                "clicked", G_CALLBACK(destroy), cli);
    gtk_widget_hide(cli->set_window);
}

void stickers_clicked(__attribute__((unused)) GtkWidget *button,
                      gpointer data) {
    client_t *cli = (client_t *)data;

    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                          "sticker_dialog"));
    
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(cli->cwindow));
    gtk_widget_show_all(dialog);

    int responce = gtk_dialog_run(GTK_DIALOG(dialog));

    if (responce == 1) {
        gtk_widget_hide(dialog);
    }
    gtk_widget_hide(dialog);
}

void sticker_1(__attribute__((unused)) GtkWidget *button,
                      gpointer data) {
    client_t *cli = (client_t *)data;
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                          "sticker_dialog"));
    gtk_widget_hide(dialog);
    gchar *message = "^s1^";
    GtkLabel *current_user = GTK_LABEL(gtk_builder_get_object
                                       (cli->builder, "current_user_lbl"));
    char *login = (char *)gtk_label_get_text(current_user);

    if (strlen(login) > 11) {
        mx_sending_invite_dialog(cli, 'c');
    }
    else {
        mx_send_message_request(message, login, cli);
        if (!strcmp(login, "#Paradise"))
            mx_insert_msg(message, cli, 0, NULL, NULL);
    }
}

void sticker_2(__attribute__((unused)) GtkWidget *button,
                      gpointer data) {
    client_t *cli = (client_t *)data;
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                          "sticker_dialog"));
    gtk_widget_hide(dialog);
    gchar *message = "^s2^";
    GtkLabel *current_user = GTK_LABEL(gtk_builder_get_object
                                       (cli->builder, "current_user_lbl"));
    char *login = (char *)gtk_label_get_text(current_user);
    
    if (strlen(login) > 11) {
        mx_sending_invite_dialog(cli, 'c');
    }
    else {
        mx_send_message_request(message, login, cli);
        if (!strcmp(login, "#Paradise"))
            mx_insert_msg(message, cli, 0, NULL, NULL);
    }
}

void sticker_3(__attribute__((unused)) GtkWidget *button,
                      gpointer data) {
    client_t *cli = (client_t *)data;
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                          "sticker_dialog"));
    gtk_widget_hide(dialog);
    gchar *message = "^s3^";
    GtkLabel *current_user = GTK_LABEL(gtk_builder_get_object
                                       (cli->builder, "current_user_lbl"));
    char *login = (char *)gtk_label_get_text(current_user);
    
    if (strlen(login) > 11) {
        mx_sending_invite_dialog(cli, 'c');
    }
    else {
        mx_send_message_request(message, login, cli);
        if (!strcmp(login, "#Paradise"))
            mx_insert_msg(message, cli, 0, NULL, NULL);
    }
}

void sticker_4(__attribute__((unused)) GtkWidget *button,
                      gpointer data) {
    client_t *cli = (client_t *)data;
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                          "sticker_dialog"));
    gtk_widget_hide(dialog);
    gchar *message = "^s4^";
    GtkLabel *current_user = GTK_LABEL(gtk_builder_get_object
                                       (cli->builder, "current_user_lbl"));
    char *login = (char *)gtk_label_get_text(current_user);
    
    if (strlen(login) > 11) {
        mx_sending_invite_dialog(cli, 'c');
    }
    else {
        mx_send_message_request(message, login, cli);
        if (!strcmp(login, "#Paradise"))
            mx_insert_msg(message, cli, 0, NULL, NULL);
    }
}

void sticker_5(__attribute__((unused)) GtkWidget *button,
                      gpointer data) {
    client_t *cli = (client_t *)data;
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                          "sticker_dialog"));
    gtk_widget_hide(dialog);
    gchar *message = "^s5^";
    GtkLabel *current_user = GTK_LABEL(gtk_builder_get_object
                                       (cli->builder, "current_user_lbl"));
    char *login = (char *)gtk_label_get_text(current_user);
    
    if (strlen(login) > 11) {
        mx_sending_invite_dialog(cli, 'c');
    }
    else {
        mx_send_message_request(message, login, cli);
        if (!strcmp(login, "#Paradise"))
            mx_insert_msg(message, cli, 0, NULL, NULL);
    }
}

void sticker_6(__attribute__((unused)) GtkWidget *button,
                      gpointer data) {
    client_t *cli = (client_t *)data;
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                          "sticker_dialog"));
    gtk_widget_hide(dialog);
    gchar *message = "^s6^";
    GtkLabel *current_user = GTK_LABEL(gtk_builder_get_object
                                       (cli->builder, "current_user_lbl"));
    char *login = (char *)gtk_label_get_text(current_user);
    
    if (strlen(login) > 11) {
        mx_sending_invite_dialog(cli, 'c');
    }
    else {
        mx_send_message_request(message, login, cli);
        if (!strcmp(login, "#Paradise"))
            mx_insert_msg(message, cli, 0, NULL, NULL);
    }
}

void sticker_7(__attribute__((unused)) GtkWidget *button,
                      gpointer data) {
    client_t *cli = (client_t *)data;
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                          "sticker_dialog"));
    gtk_widget_hide(dialog);
    gchar *message = "^s7^";
    GtkLabel *current_user = GTK_LABEL(gtk_builder_get_object
                                       (cli->builder, "current_user_lbl"));
    char *login = (char *)gtk_label_get_text(current_user);
    
    if (strlen(login) > 11) {
        mx_sending_invite_dialog(cli, 'c');
    }
    else {
        mx_send_message_request(message, login, cli);
        if (!strcmp(login, "#Paradise"))
            mx_insert_msg(message, cli, 0, NULL, NULL);
    }
}

void sticker_8(__attribute__((unused)) GtkWidget *button,
                      gpointer data) {
    client_t *cli = (client_t *)data;
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                          "sticker_dialog"));
    gtk_widget_hide(dialog);
    gchar *message = "^s8^";
    GtkLabel *current_user = GTK_LABEL(gtk_builder_get_object
                                       (cli->builder, "current_user_lbl"));
    char *login = (char *)gtk_label_get_text(current_user);
    
    if (strlen(login) > 11) {
        mx_sending_invite_dialog(cli, 'c');
    }
    else {
        mx_send_message_request(message, login, cli);
        if (!strcmp(login, "#Paradise"))
            mx_insert_msg(message, cli, 0, NULL, NULL);
    }
}

void sticker_9(__attribute__((unused)) GtkWidget *button,
                      gpointer data) {
    client_t *cli = (client_t *)data;
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                          "sticker_dialog"));
    gtk_widget_hide(dialog);
    gchar *message = "^s9^";
    GtkLabel *current_user = GTK_LABEL(gtk_builder_get_object
                                       (cli->builder, "current_user_lbl"));
    char *login = (char *)gtk_label_get_text(current_user);
    
    if (strlen(login) > 11) {
        mx_sending_invite_dialog(cli, 'c');
    }
    else {
        mx_send_message_request(message, login, cli);
        if (!strcmp(login, "#Paradise"))
            mx_insert_msg(message, cli, 0, NULL, NULL);
    }
}

void sticker_10(__attribute__((unused)) GtkWidget *button,
                      gpointer data) {
    client_t *cli = (client_t *)data;
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                          "sticker_dialog"));
    gtk_widget_hide(dialog);
    gchar *message = "^s10^";
    GtkLabel *current_user = GTK_LABEL(gtk_builder_get_object
                                       (cli->builder, "current_user_lbl"));
    char *login = (char *)gtk_label_get_text(current_user);
    
    if (strlen(login) > 11) {
        mx_sending_invite_dialog(cli, 'c');
    }
    else {
        mx_send_message_request(message, login, cli);
        if (!strcmp(login, "#Paradise"))
            mx_insert_msg(message, cli, 0, NULL, NULL);
    }
}

void sticker_11(__attribute__((unused)) GtkWidget *button,
                      gpointer data) {
    client_t *cli = (client_t *)data;
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                          "sticker_dialog"));
    gtk_widget_hide(dialog);
    gchar *message = "^s11^";
    GtkLabel *current_user = GTK_LABEL(gtk_builder_get_object
                                       (cli->builder, "current_user_lbl"));
    char *login = (char *)gtk_label_get_text(current_user);
    
    if (strlen(login) > 11) {
        mx_sending_invite_dialog(cli, 'c');
    }
    else {
        mx_send_message_request(message, login, cli);
        if (!strcmp(login, "#Paradise"))
            mx_insert_msg(message, cli, 0, NULL, NULL);
    }
}

void sticker_12(__attribute__((unused)) GtkWidget *button,
                      gpointer data) {
    client_t *cli = (client_t *)data;
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                          "sticker_dialog"));
    gtk_widget_hide(dialog);
    gchar *message = "^s12^";
    GtkLabel *current_user = GTK_LABEL(gtk_builder_get_object
                                       (cli->builder, "current_user_lbl"));
    char *login = (char *)gtk_label_get_text(current_user);
    
    if (strlen(login) > 11) {
        mx_sending_invite_dialog(cli, 'c');
    }
    else {
        mx_send_message_request(message, login, cli);
        if (!strcmp(login, "#Paradise"))
            mx_insert_msg(message, cli, 0, NULL, NULL);
    }
}

void mx_theme_1(__attribute__((unused)) GtkWidget *button, void *data) {
    client_t *cli = (client_t *)data;
    GtkCssProvider *provider = gtk_css_provider_new ();

    gtk_css_provider_load_from_path(provider,////////////////////////////
                                    "client/src/gui/glade/pink_thm.css",
                                    NULL);////////////////////////////////
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(cli->builder,
                            "set_img")),
                            "client/src/gui/glade/assets/set2.png");
    gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(cli->builder,
                            "cntc_invader")),
                            "client/src/gui/glade/assets/invader_v.png");
}

void mx_theme_2(__attribute__((unused)) GtkWidget *button, void *data) {
    client_t *cli = (client_t *)data;
    GtkCssProvider *provider = gtk_css_provider_new ();

    gtk_css_provider_load_from_path(provider,/////////////////////////////
                                    "client/src/gui/glade/green_thm.css",
                                    NULL);////////////////////////////////
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(cli->builder,
                            "set_img")),//////////////////////////////////
                            "client/src/gui/glade/assets/set3.png");
    gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(cli->builder,
                            "cntc_invader")),
                            "client/src/gui/glade/assets/invader_g.png");
}

void mx_theme_3(__attribute__((unused)) GtkWidget *button, void *data) {
    client_t *cli = (client_t *)data;
    GtkCssProvider *provider = gtk_css_provider_new ();

    gtk_css_provider_load_from_path(provider,//////////////////////////////
                                    "client/src/gui/glade/orange_thm.css",
                                    NULL);/////////////////////////////////
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(cli->builder,
                            "set_img")),///////////////////////////
                            "client/src/gui/glade/assets/set4.png");
    gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(cli->builder,
                            "cntc_invader")),
                            "client/src/gui/glade/assets/invader_o.png");
}

void mx_theme_4(__attribute__((unused)) GtkWidget *button, void *data) {
    client_t *cli = (client_t *)data;
    GtkCssProvider *provider = gtk_css_provider_new ();

    gtk_css_provider_load_from_path(provider,///////////////////////
                                    "client/src/gui/glade/style.css",
                                    NULL);//////////////////////////
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(cli->builder,
                            "set_img")),//////////////////////////////
                            "client/src/gui/glade/assets/settings.png");
    gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(cli->builder,
                            "cntc_invader")),
                            "client/src/gui/glade/assets/invader.png");
}


void on_btn_delete_msg_clicked(__attribute__((unused)) GtkWidget *button,
                               gpointer data) {
    client_t *cli = (client_t *)data;
    GtkListBox *msg_list = GTK_LIST_BOX(gtk_builder_get_object/////////
                                        (cli->builder, "msg_list"));
    GtkLabel *current_user = GTK_LABEL(gtk_builder_get_object
                                       (cli->builder, "current_user_lbl"));
    GtkListBoxRow *row = gtk_list_box_get_selected_row(msg_list);
    if (row) {
        GList *gl_row = gtk_container_get_children(GTK_CONTAINER(row));
        GList *gl_box = gtk_container_get_children(GTK_CONTAINER(gl_row->data));
        GtkLabel *snd = GTK_LABEL(gl_box->next->data);
        GtkLabel *id = GTK_LABEL(gl_box->next->next->data);

        char *username = (char *)gtk_label_get_text(current_user);
        char *sndr = (char *)gtk_label_get_text(snd);
        char *msgid = (char *)gtk_label_get_text(id);
        
        if (strcmp(username, sndr) != 0) {
            gtk_widget_hide(GTK_WIDGET(row));
            mx_delete_message_request(cli, msgid);
        }
        else
            mx_sending_invite_dialog(cli, 'd');
    }
}

void on_cntc_incoming_allow_btn_clicked(__attribute__((unused))
                                        GtkWidget *button, gpointer data) {
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

void on_cntc_incoming_decline_btn_clicked(__attribute__((unused))
                                          GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;
    GtkListBox *cntc_list = GTK_LIST_BOX(gtk_builder_get_object/////////
                                         (cli->builder, "cntc_incoming_list"));
    GtkListBoxRow *row = gtk_list_box_get_selected_row(cntc_list);
    if (row) {
        GList *gl_row = gtk_container_get_children(GTK_CONTAINER(row));
        GList *gl_box = gtk_container_get_children(GTK_CONTAINER(gl_row->data));
        GtkLabel *lbl = GTK_LABEL(gl_box->next->data);
        char *login = (char *)gtk_label_get_text(lbl);
        
        gtk_widget_hide(GTK_WIDGET(row));
        mx_decline_cntc_request(cli, login);
    }
}

void on_cntc_outgoing_remove_btn_clicked(__attribute__((unused))
                                         GtkWidget *button, gpointer data) {
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

void on_send_msg_btn_clicked(__attribute__((unused))
                             GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;
    GtkTextIter start, end;
    gchar *message;
    GtkTextView *entry = GTK_TEXT_VIEW(gtk_builder_get_object///////////
                                   (cli->builder,///////////////////////
                                   "msg_entry"));
    GtkLabel *current_user = GTK_LABEL(gtk_builder_get_object
                                       (cli->builder, "current_user_lbl"));

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(entry);
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    message = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    char *login = (char *)gtk_label_get_text(current_user);
    if (mx_valid_msg(message, login, cli)) {
        mx_send_message_request(message, login, cli);
        if (!strcmp(login, "#Paradise"))
            mx_insert_msg(message, cli, 0, NULL, NULL);
        gtk_text_buffer_set_text(buffer, "", 1);
    }
}

void on_cntc_list_selected_rows_changed(__attribute__((unused))
                                        GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;
    GtkListBox *cntc_list = GTK_LIST_BOX(gtk_builder_get_object/////////
                                         (cli->builder, "cntc_list"));
    GtkLabel *current_user_lbl = GTK_LABEL(gtk_builder_get_object
                                           (cli->builder, "current_user_lbl"));
    GtkListBoxRow *row = gtk_list_box_get_selected_row(cntc_list);
    GtkWidget *btn_del = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                           "btn_delete_msg"));
    
    if (row) {
        GList *gl_row = gtk_container_get_children(GTK_CONTAINER(row));
        GList *gl_box = gtk_container_get_children(GTK_CONTAINER(gl_row->data));
        GtkLabel *lbl = GTK_LABEL(gl_box->next->data);
        char *login = (char *)gtk_label_get_text(lbl);
        
        gtk_widget_show(btn_del);
        mx_clear_msg_list(cli);
        mx_recieve_message_list_request(login, cli);
        gtk_label_set_text(current_user_lbl, login);
    }
}

void on_chnl_list_selected_rows_changed(__attribute__((unused))
                                        GtkWidget *button, gpointer data) {
    client_t *cli = (client_t *)data;
    GtkWidget *btn_del = GTK_WIDGET(gtk_builder_get_object(cli->builder,
                                                           "btn_delete_msg"));

    GtkLabel *current_user_lbl = GTK_LABEL(gtk_builder_get_object
                                           (cli->builder, "current_user_lbl"));
    gtk_widget_hide(btn_del);
    mx_clear_msg_list(cli);
    mx_recieve_message_chnl_request(cli);
    gtk_label_set_text(current_user_lbl, "#Paradise");
}

void on_cntc_remove_btn_clicked(__attribute__((unused))
                                GtkWidget *button, gpointer data) {
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

        gtk_window_set_transient_for(GTK_WINDOW(dialog),
                                     GTK_WINDOW(cli->cwindow));
        gtk_widget_show_all(dialog);

        int responce = gtk_dialog_run(GTK_DIALOG(dialog));
        if (responce == 1) {
            gtk_label_set_text(GTK_LABEL(lgnlbl), "");
            gtk_widget_hide(dialog);
            mx_clear_msg_list(cli);
            mx_remove_cntc_request(cli, login, "cntc_list");
            GtkLabel *current_user_lbl = GTK_LABEL//////////////////////////
                                         (gtk_builder_get_object////////////
                                         (cli->builder, "current_user_lbl"));
            gtk_label_set_text(current_user_lbl,//////////////////
                               "Select contact to start chatting");
        }
        else {
            gtk_label_set_text(GTK_LABEL(lgnlbl), "");
            gtk_widget_hide(dialog);
        }
    }
}

void on_cntc_add_btn_clicked(__attribute__((unused))
                            GtkWidget *button, gpointer data) {
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
