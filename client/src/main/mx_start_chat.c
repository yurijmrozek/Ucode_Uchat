#include "client.h"

void mx_start_chat(t_chat *chat) {
    pthread_t recv_t;
    
    mx_init_gui(chat);
    pthread_create(&recv_t, NULL, mx_client_recv, (void *)chat);
    g_idle_add ((int (*)(void *))mx_show_widget, chat->window);
    gtk_main();
}
