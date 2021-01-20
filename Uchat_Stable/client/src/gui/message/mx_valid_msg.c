#include "client.h"

bool mx_valid_msg(gchar *message, char *login, client_t *cli) {
    bool valid = true;

    if (strlen(login) > 11) {
        mx_sending_invite_dialog(cli, 'c');
        return false;
    }
    if (strlen(message) < 3 || strlen(message) > 255)
        valid = false;
    if (!valid) {
        mx_sending_invite_dialog(cli, 'm');
        return false;
    }
    return true;
}
