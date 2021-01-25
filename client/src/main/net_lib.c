#include "client.h"

/* Send message to sender */
void send_message_self(const char *s, int sockfd) {
    if (write(sockfd, s, strlen(s)) < 0) {
        perror("Write to descriptor failed");
        exit(-1);
    }
}
