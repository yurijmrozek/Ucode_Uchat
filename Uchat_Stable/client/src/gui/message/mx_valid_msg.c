#include "client.h"

bool mx_valid_msg(gchar *message, char *login, client_t *cli) {
    bool valid = true;
    int c = 0;

    if (strlen(login) > 11) {
        mx_sending_invite_dialog(cli, 'c');
        return false;
    }
    if (strlen(message) < 3 || strlen(message) > 255)
        valid = false;
    for (int i = 0; message[i]; i++) {
        if (message[i] == '~' || message[i] == '^') {
            mx_sending_invite_dialog(cli, '~');
            return false;
        }
        if (!isspace(message[i]))
            c++;
    }
    if (c < 3)
        valid = false;
    if (!valid) {
        mx_sending_invite_dialog(cli, 'm');
        return false;
    }
    return true;
}
