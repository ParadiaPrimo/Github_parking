#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*LES COMMENTAIRES SONT EN FRANCAIS POUR LE MOMENT*/
void gtk_box_pack_start(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
void gtk_box_pack_end(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
static void registrationForm(GtkContainer *vbox, GtkWidget *toolbar);
static void createWindow(GtkWidget *button, gpointer data);

int main(int argc, char *argv[]) {

    GtkWidget *window;
    GtkContainer *vbox;
    GtkContainer *box;
    GtkWidget *hbox;

    GtkWidget *toolbar;
    GtkToolItem *sep;
    GtkToolItem *exitTb;
    GtkWidget *buttonArray;
    GtkWidget *buttonLabel;
    GtkWidget *button[5];

    GtkWidget *headerTitleLabel;
    gchar *headerTitle;
    GtkWidget *textLabel;
    gchar *text;

    GtkWidget *frame;
    GtkWidget *vBoxFrame;
    GtkWidget *boxButtons;
    GtkWidget *scrollbar;

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
    gtk_container_set_border_width(GTK_CONTAINER(window), 30);
    gtk_window_set_title(GTK_WINDOW(window), "PARK'CAR");
    gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);

    //SCROLLBAR
    scrollbar = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window),scrollbar);
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollbar), vbox);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

    sep = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);
    exitTb = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exitTb, -1);

    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);
    g_signal_connect(G_OBJECT(exitTb), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    headerTitle = g_locale_from_utf8("\n\n<b><big>Welcome to PARK'CAR</big></b>\n\n", -1, NULL, NULL, NULL);
    headerTitleLabel = gtk_label_new(headerTitle);
    g_free(headerTitle);
    gtk_label_set_use_markup(GTK_LABEL(headerTitleLabel), TRUE);
    gtk_label_set_justify(GTK_LABEL(headerTitleLabel), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), headerTitleLabel, FALSE, FALSE, 0);

    frame = gtk_frame_new("Discover the PARK'CAR service");
    gtk_box_pack_start(GTK_BOX(vbox), frame, FALSE, FALSE, 5);
    vBoxFrame = gtk_vbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(frame), vBoxFrame);
    textLabel = gtk_label_new("With PARK'CAR, you can book a car space!\nYou can modify or cancel your oder until your scheduled day of entry.\nPay for your parking online.\n");
    gtk_box_pack_start(GTK_BOX(vBoxFrame), textLabel, FALSE, FALSE, 10);

    buttonArray = gtk_table_new(4, 4, TRUE);
    buttonLabel = gtk_label_new(buttonArray);
    /*boxButtons = gtk_vbox_new(TRUE, 0);
    gtk_box_pack_start(GTK_BOX(boxButtons), vbox, FALSE, FALSE, 5);
    gtk_container_add(GTK_CONTAINER(box), boxButtons);printf("ok");
    gtk_container_set_border_width(GTK_CONTAINER(box), 50);*/
    gtk_box_pack_start(GTK_BOX(vbox), buttonArray, FALSE, FALSE, 20);

    button[0] = gtk_button_new_with_label("         Log in          ");
    button[1] = gtk_button_new_with_label("          Sign in        ");
    button[2] = gtk_button_new_with_label("    Check our parking    ");
    button[3] = gtk_button_new_with_label("   Consult our offers    ");
    button[4] = gtk_button_new_with_label(" Book your parking space ");

    /*gtk_box_pack_start(GTK_BOX(boxButtons), button[0], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(boxButtons), button[1], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(boxButtons), button[2], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(boxButtons), button[3], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(boxButtons), button[4], FALSE, FALSE, 0);*/

    gtk_table_attach(GTK_TABLE(buttonArray), button[0], 3, 4, 1, 2, !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(buttonArray), button[1], 4, 5, 1, 2, !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(buttonArray), button[2], 3, 4, 2, 3, !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(buttonArray), button[3], 3, 4, 3, 4, !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(buttonArray), button[4], 3, 4, 4, 5, !GTK_FILL, !GTK_EXPAND, 0, 10);

    g_signal_connect(button[0], "clicked", G_CALLBACK(createWindow), NULL);


    //DISPLAY THE WINDOW
    gtk_widget_show_all(window);

    gtk_main();

  return 0;
}
static void createWindow(GtkWidget *button, gpointer data){
    GtkWidget *window;
    GtkWidget *label;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    label = gtk_label_new ("Hello GNOME!");
    gtk_container_add (GTK_CONTAINER (window), label);
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 100);
    gtk_widget_show_all (window);
}
