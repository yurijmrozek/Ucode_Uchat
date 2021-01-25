#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdbool.h>

#include <sqlite3.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gio/gio.h>
#include "../../libraries/include/cJSON.h"

typedef struct {
    int sockfd;
    int con_port;
    char *con_ip;
    GtkWidget *awindow;
    GtkWidget *cwindow;
    GtkWidget *set_window;
    GtkBuilder *builder;    
}               client_t;

void mx_valid_argv(int argc, char **argv, client_t *cli);
void mx_create_connection(client_t *cli);
void mx_init_authoriz_gui(client_t *cli);
void mx_init_chat_gui(client_t *cli);
void *mx_read_server(void *arg);
void destroy(client_t *cli);
bool mx_valid_reg_creden(client_t *cli);
bool mx_valid_log_creden(client_t *cli);
void mx_login_request(client_t *cli);
void mx_register_request(client_t *cli);
void send_message_self(const char *s, int sockfd);
void mx_json_manager(char buff_in[], client_t *cli);
void mx_login_responce(cJSON *j_responce, client_t *cli);
void mx_register_responce(cJSON *j_responce, client_t *cli);
void mx_creden_accepted(client_t *cli);
void mx_add_cntc_request(client_t *cli, char *username);
void mx_sending_invite_dialog(client_t *cli, char valid);
void mx_add_new_cntc_responce(cJSON *j_responce, client_t *cli);
void mx_insert_cntc_list(char *username, client_t *cli, char *icon);
void mx_clear_cntc_list(client_t *cli);
void mx_clear_chat(client_t *cli);
void mx_getup_cntc(cJSON *j_responce, client_t *cli);
void mx_accept_cntc_request(client_t *cli, char *login);
void mx_getup_inv(cJSON *j_responce, client_t *cli);
void mx_invite_answer_responce(cJSON *j_responce, client_t *cli);
void mx_notification_dialog(client_t *cli, char *username, char flag);
void mx_decline_cntc_request(client_t *cli, char *username);
void mx_remove_cntc_request(client_t *cli, char *username, char *type);
void mx_insert_msg(gchar *message, client_t *cli, int pos, char *msgsender,
                   char *msgid);
void mx_clear_msg_list(client_t *cli);
bool mx_valid_msg(gchar *message, char *login, client_t *cli);
void mx_send_message_request(gchar *message, char *username, client_t *cli);
void mx_recieve_message_list_request(char *login, client_t *cli);
void mx_getup_msgs(cJSON *j_responce, client_t *cli);
void mx_scroll_to_down(client_t *cli);
void mx_getup_new_msg(cJSON *j_responce, client_t *cli);
void mx_delete_message_request(client_t *cli, char *msgid);
void mx_getup_new_chnl_msg(cJSON *j_responce, client_t *cli);
void mx_insert_chnl_msg(char *sender, char *message, client_t *cli, int pos);
void mx_recieve_message_chnl_request(client_t *cli);
void mx_getup_chnl_msgs(cJSON *j_responce, client_t *cli);
