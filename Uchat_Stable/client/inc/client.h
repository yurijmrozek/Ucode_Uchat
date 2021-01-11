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
    GtkBuilder *builder;
}               client_t;

void mx_valid_argv(int argc, char **argv, client_t *cli);
void mx_create_connection(client_t *cli);
void mx_init_autoriz_gui(client_t *cli);
void *mx_read_server(void *arg);
void destroy(client_t *cli);
bool mx_valid_reg_creden(client_t *cli);
bool mx_valid_log_creden(client_t *cli);
void mx_login_request(client_t *cli);
void mx_register_request(client_t *cli);
void send_message_self(const char *s, int sockfd);