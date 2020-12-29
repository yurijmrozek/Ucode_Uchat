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

//enum
typedef enum e_type_db {
    DB_NEW_MESSAGE = 0,
    DB_OLD_MESSAGE,
    DB_SECOND,
    DB_MILISECOND,
    DB_MICROSECOND
}            t_type_db;
//enum

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
guint64 mx_get_time(gint8 type);
int mx_manage_socket_db(t_database *t_db, char *username,
                         int socket1);
int mx_clean_socket_db(t_database *t_db, int socket1);
int mx_create_user_table(t_database *t_db);
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
void mx_recv_client(t_server *server, int socket1);
//responce

//json
void mx_json_manager(char Buffer[1024], t_server *server, int socket1);
//json
