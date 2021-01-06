#include "client.h"

// static char *strnew(const int size) {
//     char *strnew = malloc(size < 0 ? size : size + 1);
    
//     for (int i = 0; strnew && i <= size; ++i)
//         strnew[i] = '\0';
//     return strnew;
// }

// static int count_words(const char *str, char delimiter) {
//     int counter = 0;
    
//     for (;*str; ++str) {
//         if (*str != delimiter && ++counter)
//             for (;*(str + 1) && *str != delimiter; ++str);
//     }
//     return counter;
// }

// static char **strsplit(const char *s, char c) {
//     int xcount_words = 0;
    
//     if (!s || (xcount_words = count_words(s, c)) < 0)
//         return NULL;
    
//     char **split = malloc(sizeof(char*) * xcount_words + 1);
//     split[xcount_words] = NULL;
    
//     for (int i = 0, len = 0; i < xcount_words; ++i, s += len, len = 0) {
//         for (; *s == c; ++s);
//         for (; s[len] != c; ++len);
//         split[i] = strnew(len);
//         strncpy(split[i], s, len);
//     }
//     return split;
// }

void mx_login_handl_res(cJSON *j_responce, t_chat *chat) {
    cJSON *j_valid = cJSON_GetObjectItemCaseSensitive(j_responce, "valid");
    // cJSON *j_cont;
    char *valid = strdup(j_valid->valuestring);
    // if ((j_cont = cJSON_GetObjectItemCaseSensitive(j_responce, "contacts"))) {
    //     char **contact = strsplit(j_cont->valuestring, ',');
    //     if (!strcmp(valid, "true"))
    //     for (int i = 0; contact[i]; i++)
    //         mx_create_contact(chat, contact[i]);
    // }
    


    if (!strcmp(valid, "true"))
        autorized_accept(chat);
    else if (!strcmp(valid, "us_exist"))
        autorized_decline(chat, 'e');
    else if (!strcmp(valid, "busy"))
        autorized_decline(chat, 'b');
    else
        autorized_decline(chat, 'n');
}
