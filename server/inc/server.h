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
#include <glib.h>
#include "../../libraries/include/cJSON.h"
//libs

//struct
typedef struct s_uchat_server {
    int flag;
    int result;
    int socket0;
    int argc;
    char **argv;
    int port;
}              t_server;
//struct

//server
int mx_create_server(t_server *server);
int mx_thread_create(t_server *server);
int mx_valid_argv(t_server *server);
void *mx_accept_user(void *data);
//server

//responce
void mx_login_responce(cJSON *j_request, int socket1);
void mx_recv_client(t_server *server, int socket1);
//responce

//json
void mx_json_manager(char Buffer[1024], t_server *server, int socket1);
//json
