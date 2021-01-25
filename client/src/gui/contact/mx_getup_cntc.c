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

void mx_getup_cntc(cJSON *j_responce, client_t *cli) {
    cJSON *j_cont;
    cJSON *j_cont_state;
    char **cntcarr = NULL;
    char **cntcstate = NULL;

    j_cont = cJSON_GetObjectItemCaseSensitive(j_responce, "cntc_list");
    j_cont_state = cJSON_GetObjectItemCaseSensitive(j_responce,///////
                                                    "cntc_list_state");
    
    mx_clear_cntc_list(cli);
    cntcarr = strsplit(j_cont->valuestring, ',');
    cntcstate = strsplit(j_cont_state->valuestring, ',');
    for (int i = 0; cntcarr[i]; i++) {
        mx_insert_cntc_list(cntcarr[i], cli, cntcstate[i]);
        free(cntcarr[i]);
        free(cntcstate[i]);
    }
    free(cntcarr);
    free(cntcstate);
}
