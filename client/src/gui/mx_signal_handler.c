#include "client.h"

void quit_chat() {
    usleep(100);
    gtk_main_quit();
}

void autorized_accept(t_chat *chat) {
    printf("login accepted\n");
    if (chat->builder) {
        GtkStack *stk = GTK_STACK(gtk_builder_get_object(chat->builder,
                                                         "main_stack"));
        gtk_stack_set_visible_child_name(stk, "register_page0");
    }
}

void on_logout_btn_clicked(GtkButton *btn_back, t_chat *chat) {
    GtkStack *stk = GTK_STACK(gtk_builder_get_object(chat->builder,
                                                         "main_stack"));
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