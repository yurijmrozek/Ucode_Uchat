#include "client.h"

void mx_json_manager(char buff_in[], client_t *cli) {
    cJSON *j_responce = cJSON_Parse(buff_in);

    cJSON *j_action = cJSON_GetObjectItemCaseSensitive(j_responce,
                                                       "action");
    if (!strcmp(j_action->valuestring, "signin_responce"))
        mx_login_responce(j_responce, cli);
    else if (!strcmp(j_action->valuestring, "signup_responce"))
        mx_register_responce(j_responce, cli);
    else if (!strcmp(j_action->valuestring, "add_new_cntc_responce"))
        mx_add_new_cntc_responce(j_responce, cli);
    else if (!strcmp(j_action->valuestring, "getup_cntc"))
        mx_getup_cntc(j_responce, cli);
    else if (!strcmp(j_action->valuestring, "getup_inv"))
        mx_getup_inv(j_responce, cli);
    else if (!strcmp(j_action->valuestring, "invite_answer"))
        mx_invite_answer_responce(j_responce, cli);
    else if (!strcmp(j_action->valuestring, "recieved_friend_invite"))
        mx_notification_dialog(cli, NULL, 'i');
    else if (!strcmp(j_action->valuestring, "remove_friend")) {
        cJSON *j_username = cJSON_GetObjectItemCaseSensitive(j_responce,
                                                             "username");
        mx_clear_msg_list(cli);
        GtkLabel *current_user_lbl = GTK_LABEL(gtk_builder_get_object/////////
                                           (cli->builder, "current_user_lbl"));
        gtk_label_set_text(current_user_lbl,/////////////////
                           "Select contact to start chatting");
        mx_notification_dialog(cli, j_username->valuestring, 'r');
    }
    else if (!strcmp(j_action->valuestring, "getup_msgs"))
        mx_getup_msgs(j_responce, cli);
    else if (!strcmp(j_action->valuestring, "getup_new_msg"))
        mx_getup_new_msg(j_responce, cli);
    else if (!strcmp(j_action->valuestring, "getup_new_chnl_msg"))
        mx_getup_new_chnl_msg(j_responce, cli);
    else if (!strcmp(j_action->valuestring, "getup_chnl_msgs"))
        mx_getup_chnl_msgs(j_responce, cli);

    cJSON_Delete(j_responce);
}
