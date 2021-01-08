#include "client.h"

void destroy(t_chat *chat) {
    mx_send_logout(chat);
    gtk_main_quit();
}

void autorized_decline(t_chat *chat, char flag) {
    GtkLabel *err_label = GTK_LABEL(gtk_builder_get_object
                                   (chat->builder, "login_err_empty"));
    if (flag == 'n')
        gtk_label_set_text(err_label, "Invalid login or password."  \
                                      "\nSwitch toggle 'new user' " \
                                      "to register.\n");            \
    else if (flag == 'e')
        gtk_label_set_text(err_label, "Login was already taken. Try other!\n");
    else if (flag == 'b')
        gtk_label_set_text(err_label, "User is currently busy.\n");
}

void autorized_accept(t_chat *chat) {
    if (chat->builder) {
        GtkStack *stk = GTK_STACK(gtk_builder_get_object(chat->builder,
                                                         "main_stack"));
        gtk_stack_set_visible_child_name(stk, "uchat_page0");
    }
}

void on_contact_btn_add_clicked(void *data, t_chat *chat) {
    mx_valid_csearch(chat);
}

void on_logout_btn_clicked(void *data, t_chat *chat) {
    GtkStack *stk = GTK_STACK(gtk_builder_get_object(chat->builder,
                                                     "main_stack"));
    mx_send_logout(chat);
    gtk_stack_set_visible_child_name(stk, "login_page0");
}

void on_login_btn_clicked(GtkButton *btn_login, t_chat *chat) {
    GtkToggleButton *toggled = GTK_TOGGLE_BUTTON(gtk_builder_get_object
                                              (chat->builder, "reg_toggle"));
    if (mx_valid_login_gui(chat) != 2) {
        if (gtk_toggle_button_get_active(toggled))
		    mx_register_request(chat);
        else
            mx_login_request(chat);
    }
}
