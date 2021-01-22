#include "client.h"

static char *strnew(const int size) {
    char *strnew = malloc(size < 0 ? size : size + 1);
    for (int i = 0; strnew && i <= size; ++i)
        strnew[i] = '\0';
    return strnew;
}

static int count_words(const char *str, char delimiter) {
    int counter = 0;
    for (;*str; ++str) {
        if (*str != delimiter && ++counter)
            for (;*(str + 1) && *str != delimiter; ++str);
    }
    return counter;
}

static char **strsplit(const char *s, char c) {
    int xcount_words = 0;
    if (!s || (xcount_words = count_words(s, c)) < 0)
        return NULL;
    char **split = malloc(sizeof(char*) * xcount_words + 1);
    split[xcount_words] = NULL;
    for (int i = 0, len = 0; i < xcount_words; ++i, s += len, len = 0) {
        for (; *s == c; ++s);
        for (; s[len] != c; ++len);
        split[i] = strnew(len);
        strncpy(split[i], s, len);
    }
    return split;
}

void mx_getup_chnl_msgs(cJSON *j_responce, client_t *cli) {
    char **msgarr = NULL;
    char **msgsender = NULL;
    int pos = 0;
    bool valid = false;

    GtkLabel *current_user_lbl = GTK_LABEL(gtk_builder_get_object
                                           (cli->builder, "current_user_lbl"));

    cJSON *j_msg = cJSON_GetObjectItemCaseSensitive(j_responce, "message_list");
    cJSON *j_msg_sender = cJSON_GetObjectItemCaseSensitive(j_responce,///////
                                                           "message_sender");
    cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_responce,
                                                         "username");
    char *cur_uslbl = strdup(gtk_label_get_text(current_user_lbl));

    msgarr = strsplit(j_msg->valuestring, '~');
    msgsender = strsplit(j_msg_sender->valuestring, ',');

    if (!strcmp(cur_uslbl, "#Paradise"))
        valid = true;
    if (valid) {
        for (int i = 0; msgarr[i]; i++) {
            if (!strcmp(j_username->valuestring, msgsender[i]))
                pos = 0;
            else
                pos = 1;
            mx_insert_chnl_msg(msgsender[i], msgarr[i], cli, pos);
            free(msgarr[i]);
            free(msgsender[i]);
        }
    }
    free(cur_uslbl);
    free(msgarr);
    free(msgsender);
}
