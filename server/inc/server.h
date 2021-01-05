#pragma once

//sys
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <time.h> 
#include <locale.h>
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <pthread.h>
//sys

//libs
#include <sqlite3.h>
#include <glib.h>
#include "../../libraries/include/cJSON.h"
//libs

//struct
typedef struct s_database {
    sqlite3 *db;
    gint64 u_id;
    int u_date;
}              t_database;

typedef struct s_uchat_server {
    t_database *t_db;
    int flag;
    int result;
    int socket0;
    int argc;
    char **argv;
    int port;
}              t_server;
//struct

//db
int mx_oc_db();
int mx_find_logpass_db(t_database *t_db, char *username, char *password);
int mx_find_login_db(t_database *t_db, char *username);
void mx_insert_user(t_database *t_db, char *username, char *password);
void mx_log_out(t_server *server, int socket1);
int mx_setactive_user(t_database *t_db, char *username, int flag);
int mx_get_id_socket(t_database *t_db, int socket1);
int mx_get_id_login(t_database *t_db, char *login);
char *mx_get_login_id(t_database *t_db, int id);
int mx_find_similar_cont(t_database *t_db, char *login, int socket1);
void mx_add_contact_db(t_database *t_db, char *login, int socket1);
char **mx_send_contact(t_database *t_db, int socket1);
int mx_manage_socket_db(t_database *t_db, char *username,
                         int socket1);
int mx_clean_socket_db(t_database *t_db, int socket1);
void mx_create_user_table(t_database *t_db);
int mx_user_online(t_database *t_db, char *username);
//db

//server
int mx_create_server(t_server *server);
int mx_thread_create(t_server *server);
int mx_valid_argv(t_server *server);
void *mx_accept_user(void *data);
void mx_daemon(void);
//server

//responce
void mx_register_user(t_server *server, cJSON *j_request, int socket1);
void mx_login_responce(t_server *server, cJSON *j_request, int socket1);
void mx_add_contact(t_server *server, cJSON *j_request, int socket1);
void mx_recv_client(t_server *server, int socket1);
//responce

//json
void mx_json_manager(char Buffer[1024], t_server *server, int socket1);
//json
