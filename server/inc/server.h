#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>

/* Server libraries */
#include "../../libraries/include/cJSON.h"
#include <sqlite3.h>

#define MAX_CLIENTS 128
#define BUFFER_SZ 2048
#define ARRLEN(s) (sizeof(s) / sizeof(*s))

static _Atomic unsigned int cli_count = 0;
static int uid = 10;

/* Client structure */
typedef struct {
    struct sockaddr_in addr; /* Client remote address */
    int connfd;              /* Connection file descriptor */
    int uid;                 /* Client unique identifier */
    char name[32];           /* Client name */
    sqlite3 *db;
} client_t;

client_t *clients[MAX_CLIENTS];

static char topic[BUFFER_SZ/2];

/* Functions */
int mx_create_server(char **argv);
void *mx_handle_client(void *arg);
void mx_json_manager(char buff_in[], int connfd, client_t *cli);

void mx_login_responce(cJSON *j_request, int connfd, sqlite3 *db);
void mx_register_responce(cJSON *j_request, int connfd, sqlite3 *db);
void mx_add_new_cntc_responce(cJSON *j_request, int connfd, sqlite3 *db);
void mx_send_friend_invite(sqlite3 *db, char *username);

sqlite3 *mx_get_db(sqlite3 *tmp_db);
void mx_create_table(sqlite3 *tmp_db);
int mx_check_uonline_status(sqlite3 *db, char *username);
int mx_search_user(sqlite3 *db, char *username);
int mx_confirm_ucredentials(sqlite3 *db, char *username, char *password);
void mx_insert_client_socket(sqlite3 *db, char *username, int connfd);
void mx_create_new_user(sqlite3 *db, char *username, char *password);
int mx_logout_event_db(int connfd, sqlite3 *db);
int mx_find_similar_cntc_db(sqlite3 *db, char *username, int connfd);
int mx_get_id_login(sqlite3 *db, char *username);
int mx_get_id_socket(sqlite3 *db, int connfd);
char *mx_get_login_id(sqlite3 *db, int id);
int mx_get_socket_id(sqlite3 *db, int id);
int mx_finde_invite_rev(sqlite3 *db, char *username, int connfd);
int mx_manage_cntc_db(sqlite3 *db, int connfd,//////////////
                      char *username, int state, int action);
int mx_manage_message_db(sqlite3 *db, int uid, int cid, char *message,
                         char *msgid, int action);
void mx_init_client_db(sqlite3 *db, int connfd);
void mx_send_cntc(sqlite3 *db, int connfd);
void mx_init_client_db(sqlite3 *db, int connfd);
void mx_accept_friend_invite(cJSON *j_request, int connfd, sqlite3 *db);
int mx_find_invite(sqlite3 *db, char *username, int connfd);
void mx_decline_friend_invite(cJSON *j_request, int connfd, sqlite3 *db);
void mx_remove_cntc_responce(cJSON *j_request, int connfd, sqlite3 *db);
void mx_insert_new_message(cJSON *j_request, int connfd, sqlite3 *db);
void mx_getup_messages(cJSON *j_request, int connfd, sqlite3 *db);
void mx_getup_new_message(int uid, char *message, char *username, 
                          int sockfd, sqlite3 *db, char *state);
void mx_remove_message(cJSON *j_request, sqlite3 *db);
int mx_manage_chnl_db(sqlite3 *db, int uid, char *message, int action);
void mx_getup_new_chnl_message(int uid, cJSON *j_message, sqlite3 *db);
void mx_getup_chnl_messages(int connfd, sqlite3 *db);
char *mx_return_id_msg(sqlite3 *db, int uid, int cid, char *message);   

/* Net Lib */
void print_client_addr(struct sockaddr_in addr);
void strip_newline(char *s);
void send_active_clients(int connfd);
void send_message_client(char *s, int uid);
void send_message_self(const char *s, int connfd);
void send_message_all(cJSON *j_responce, sqlite3 *db, int connfd);
void send_message(char *s, int uid);
void queue_delete(int uid);
void queue_add(client_t *cl);
char *_strdup(const char *s);
int mx_daemon(void);
