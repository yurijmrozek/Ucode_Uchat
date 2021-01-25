#include "client.h"

static char *strnew(const int size) {
    char *strnew = malloc(size < 0 ? size : size + 1);

    for (int i = 0; strnew[i] && i <= size; ++i)
        strnew[i] = '\0';
    return strnew; 
}

static char *strjoin(const char *s1, const char *s2) {
    char *result = NULL;

    if (!s1 && !s2)
        return NULL;
    else if (!s1)
        return strdup(s2);
    else if (!s2)
        return strdup(s1);
    
    result = strnew(strlen(s1) + strlen(s2));
    strcpy(result, s1);
    result = strcat(result, s2);
    return result;
}

static void on_size(GtkWidget *label, GtkAllocation *alloc, gpointer data) {
    data = (void *)data;
    gtk_widget_set_size_request(label, alloc->width - 2, -1);
}

void mx_insert_chnl_msg(char *sender, char *message, client_t *cli, int pos) {
    GtkListBox *msg_list = GTK_LIST_BOX(gtk_builder_get_object/////
                                        (cli->builder, "msg_list"));
    GtkStyleContext *context;
    GtkStyleContext *context1;

    GtkWidget *row, *hbox, *msg, *sndr;

    row = gtk_list_box_row_new();
    hbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    sndr = gtk_label_new(sender);

    if (message[0] == '^') {
        char *img_path = "client/src/gui/glade/assets/";
        img_path = strjoin(img_path, message);
        char *res = strjoin(img_path, ".png");
        free(img_path);
        GtkWidget *img = gtk_image_new_from_file(res);

        gtk_container_add(GTK_CONTAINER(row), hbox);

        if (pos == 0) {
            context1 = gtk_widget_get_style_context(GTK_WIDGET(sndr));

            gtk_widget_set_margin_top(img, 10);
            gtk_widget_set_margin_bottom(img, 10);
            gtk_widget_set_margin_start(row, 300);
            gtk_widget_set_margin_end(sndr, 20);
        }

        else if (pos == 1) {
            context1 = gtk_widget_get_style_context(GTK_WIDGET(sndr));
            gtk_style_context_add_class(context1, "sndr_intext");

            gtk_widget_set_margin_end(row, 300);
            gtk_widget_set_margin_top(img, 10);
            gtk_widget_set_margin_bottom(img, 10);
            gtk_widget_set_margin_start(row, 10);
            gtk_widget_set_margin_end(sndr, 20);
            gtk_box_pack_start(GTK_BOX(hbox), sndr, FALSE, FALSE, 0);
        }

        gtk_box_pack_start(GTK_BOX(hbox), img, FALSE, FALSE, 0);
        gtk_container_add(GTK_CONTAINER(msg_list), row);

        gtk_widget_show_all(row);
        gtk_widget_show(img);
        if (pos == 1)
            gtk_widget_show(sndr);
        mx_scroll_to_down(cli);
        free(res);
    }
    else {
        msg = gtk_label_new(message);
        gtk_misc_set_alignment(GTK_MISC(msg), 0, 0.5);
        g_signal_connect(G_OBJECT(msg), "size-allocate",
                        G_CALLBACK(on_size), NULL);
        gtk_label_set_use_markup(GTK_LABEL(msg), TRUE);
        gtk_label_set_line_wrap(GTK_LABEL(msg), TRUE);
        gtk_label_set_line_wrap_mode(GTK_LABEL(msg), PANGO_WRAP_WORD_CHAR);

        gtk_container_add(GTK_CONTAINER(row), hbox);
        if (pos == 0) {
            context = gtk_widget_get_style_context(GTK_WIDGET(msg));
            context1 = gtk_widget_get_style_context(GTK_WIDGET(sndr));
            gtk_style_context_add_class(context, "msg_intext");

            gtk_widget_set_margin_start(row, 300);
            gtk_widget_set_margin_end(msg, 10);
            gtk_widget_set_margin_end(sndr, 20);
        }

        else if (pos == 1) {
            context = gtk_widget_get_style_context(GTK_WIDGET(msg));
            context1 = gtk_widget_get_style_context(GTK_WIDGET(sndr));
            gtk_style_context_add_class(context, "msg_outext");
            gtk_style_context_add_class(context1, "sndr_intext");

            gtk_widget_set_margin_end(row, 300);
            gtk_widget_set_margin_start(row, 10);
            gtk_widget_set_margin_end(sndr, 20);
            gtk_box_pack_start(GTK_BOX(hbox), sndr, FALSE, FALSE, 0);
        }

        gtk_box_pack_start(GTK_BOX(hbox), msg, FALSE, FALSE, 0);
        gtk_container_add(GTK_CONTAINER(msg_list), row);

        gtk_widget_show_all(row);
        if (pos == 1)
            gtk_widget_show(sndr);
        gtk_widget_show(msg);
        mx_scroll_to_down(cli);
    }
}
