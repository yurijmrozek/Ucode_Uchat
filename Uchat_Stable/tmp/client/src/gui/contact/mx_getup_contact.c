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

void mx_getup_contact(cJSON *j_responce, t_chat *chat) {
    GtkLabel *err_label = GTK_LABEL(gtk_builder_get_object
                                   (chat->builder, "contact_lbl_err"));
    cJSON *j_cont;
    char **contarr = NULL;

    gtk_label_set_text(err_label, "");
    mx_clear_cont_row(chat);
    if ((j_cont = cJSON_GetObjectItemCaseSensitive(j_responce, "contacts"))) {
        contarr = strsplit(j_cont->valuestring, ',');
        for (int i = 0; contarr[i]; i++) {
            mx_create_contact(chat, contarr[i]);
            free(contarr[i]);
        }
    }
    free(contarr);
}
