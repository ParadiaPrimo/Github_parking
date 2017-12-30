#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void gtk_box_pack_start(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
void gtk_box_pack_end(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
void gtk_entry_set_visibility(GtkEntry *entry, gboolean visible);

int main(int argc, char *argv[]) {

    GtkWidget *window;
    GtkWidget *vbox;

    GtkWidget *toolbar;
    GtkToolItem *sep;
    GtkToolItem *exitTb;
    GtkToolItem *undo;

    GtkWidget *headerTitleLabel;
    gchar *headerTitle;
    GtkWidget *textArray;
    GtkWidget *subTitleLabel[3];
    gchar *subTitle[3];
    GtkWidget *textLabel[3];
    gchar *text[3];
    GtkWidget *optionsArray;
    GtkWidget *optionsLabel;
    GtkWidget *available;
    GtkWidget *unavailable;
    int idPage;
    //INITIALIZATION OF GTK
    gtk_init(&argc, &argv);

    //COLOR SET ON THE BACKGROUND
    GdkColor color;
    color.red = 0x00C0;
    color.green = 0x9887;
    color.blue = 0xF888;

    //CREATION OF THE MAIN WINDOW
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);
    gtk_window_set_title(GTK_WINDOW(window), "PARK'CAR");
    gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);

    vbox = gtk_vbox_new(FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    //TOOLBAR
    toolbar = gtk_toolbar_new();
        gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
        undo = gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
        gtk_toolbar_insert(GTK_TOOLBAR(toolbar), undo, 0);
        sep = gtk_separator_tool_item_new();
        gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, 1);
        exitTb = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
        gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exitTb, 2);

        gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);
        g_signal_connect(G_OBJECT(exitTb), "clicked", G_CALLBACK(gtk_main_quit), NULL);
        g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

        headerTitle = g_locale_from_utf8("\n\n\n<span size =\"25\">PARK'CAR OFFERS</span>\n\n\n<span size =\"12\">Choose the subscription that works for you</span>\n\n", -1, NULL, NULL, NULL);
        headerTitleLabel = gtk_label_new(headerTitle);
        g_free(headerTitle);
        gtk_label_set_use_markup(GTK_LABEL(headerTitleLabel), TRUE);
        gtk_label_set_justify(GTK_LABEL(headerTitleLabel), GTK_JUSTIFY_CENTER);
        gtk_box_pack_start(GTK_BOX(vbox), headerTitleLabel, FALSE, FALSE, 0);

    textArray = gtk_table_new(3, 1, TRUE);
        gtk_box_pack_start(GTK_BOX(vbox), textArray, FALSE, FALSE, 0);
        subTitle[0] = g_locale_from_utf8("<span size =\"5\">Classic</span>\n\n<span size =\"5\">29,99 euros</span><sup>   per month</sup>\n", -1, NULL, NULL, NULL);
        subTitleLabel[0] = gtk_label_new(subTitle[0]);
        g_free(subTitle[0]);
        gtk_label_set_use_markup(GTK_LABEL(subTitleLabel[0]), TRUE);
        gtk_label_set_justify(GTK_LABEL(subTitleLabel[0]), GTK_JUSTIFY_CENTER);
        gtk_box_pack_start(GTK_BOX(vbox), subTitleLabel[0], FALSE, FALSE, 0);
        gtk_table_attach(GTK_TABLE(textArray), subTitleLabel[0], 0, 1, 0, 3, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 50, 50);


    optionsArray = gtk_table_new(3, 2, TRUE);
    optionsLabel = gtk_label_new(optionsArray);
    gtk_label_set_justify(GTK_LABEL(optionsLabel), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), optionsArray, FALSE, FALSE, 0);
    available = gtk_label_new("Available");
    unavailable = gtk_label_new("Not available");

        text[0] = g_locale_from_utf8("<span>Park your car</span>\n", -1, NULL, NULL, NULL);
        textLabel[0] = gtk_label_new(text[0]);
        g_free(text[0]);

        gtk_label_set_use_markup(GTK_LABEL(textLabel[0]), TRUE);
        gtk_label_set_justify(GTK_LABEL(textLabel[0]), GTK_JUSTIFY_LEFT);
        //gtk_box_pack_start(GTK_BOX(vbox), textLabel[0], FALSE, FALSE, 0);
        gtk_table_attach(GTK_TABLE(optionsArray), textLabel[0], 0, 1, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
        gtk_table_attach(GTK_TABLE(optionsArray), available, 1, 2, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

        text[1] = g_locale_from_utf8("<span>Car wash</span>\n", -1, NULL, NULL, NULL);
        textLabel[1] = gtk_label_new(text[1]);
        g_free(text[1]);
        gtk_label_set_use_markup(GTK_LABEL(textLabel[1]), TRUE);
        gtk_label_set_justify(GTK_LABEL(textLabel[1]), GTK_JUSTIFY_LEFT);
        //gtk_box_pack_start(GTK_BOX(vbox), textLabel[1], FALSE, FALSE, 0);
        gtk_table_attach(GTK_TABLE(optionsArray), textLabel[1], 0, 1, 1, 2, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
        gtk_table_attach(GTK_TABLE(optionsArray), unavailable, 1, 2, 1, 2, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

        text[2] = g_locale_from_utf8("<span>Filling up the gas tank</span>\n", -1, NULL, NULL, NULL);
        textLabel[2] = gtk_label_new(text[2]);
        g_free(text[2]);
        gtk_label_set_use_markup(GTK_LABEL(textLabel[2]), TRUE);
        gtk_label_set_justify(GTK_LABEL(textLabel[2]), GTK_JUSTIFY_LEFT);
        //gtk_box_pack_start(GTK_BOX(vbox), textLabel[2], FALSE, FALSE, 0);
        gtk_table_attach(GTK_TABLE(optionsArray), textLabel[2], 0, 1, 2, 3, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
        gtk_table_attach(GTK_TABLE(optionsArray), unavailable, 1, 2, 2, 3, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    subTitle[1] = g_locale_from_utf8("\n\n<span size =\"5\">Premium</span>\n\n<span size =\"5\">46,99 euros</span><sup>   per month</sup>", -1, NULL, NULL, NULL);
    subTitleLabel[1] = gtk_label_new(subTitle[1]);
    g_free(subTitle[1]);
    gtk_label_set_use_markup(GTK_LABEL(subTitleLabel[1]), TRUE);
    gtk_label_set_justify(GTK_LABEL(subTitleLabel[1]), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), subTitleLabel[1], FALSE, FALSE, 0);
    gtk_table_attach(GTK_TABLE(textArray), subTitleLabel[1], 0, 1, 3, 6, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 50, 50);

    subTitle[2] = g_locale_from_utf8("\n\n<span size =\"5\">Premium Plus</span>\n\n<span size =\"5\">78,99 euros</span><sup>   per month</sup>", -1, NULL, NULL, NULL);
    subTitleLabel[2] = gtk_label_new(subTitle[2]);
    g_free(subTitle[2]);
    gtk_label_set_use_markup(GTK_LABEL(subTitleLabel[2]), TRUE);
    gtk_label_set_justify(GTK_LABEL(subTitleLabel[2]), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), subTitleLabel[2], FALSE, FALSE, 0);
    gtk_table_attach(GTK_TABLE(textArray), subTitleLabel[2], 1, 2, 0, 6, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 50, 50);

    //DISPLAY THE WINDOW
    gtk_widget_show_all(window);

    gtk_main();

  return 0;
}
