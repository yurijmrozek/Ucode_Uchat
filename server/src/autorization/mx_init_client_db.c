#include "server.h"

void mx_init_client_db(t_database *t_db, int socket1) {
    mx_send_contacts(t_db, socket1);
}
