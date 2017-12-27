#include <gtk/gtk.h>

GtkWidget* gtk_hbox_new(gboolean homogeneous, gint spacing);
GtkWidget* gtk_vbox_new(gboolean homogeneous, gint spacing);
void gtk_box_pack_start(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
void gtk_box_pack_end(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);

int main(int argc, char *argv[]) {

    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *hbox;

    GtkWidget *toolbar;
    GtkToolItem *sep;
    GtkToolItem *exitTb;
    GtkWidget *button[4];

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
    hbox = gtk_hbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_add(GTK_CONTAINER(window), hbox);

    toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

    sep = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);
    exitTb = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exitTb, -1);

    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);
    g_signal_connect(G_OBJECT(exitTb), "clicked",
        G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);
    button[0] = gtk_button_new_with_label("Log in");
    button[1] = gtk_button_new_with_label("Check our parking");
    button[2] = gtk_button_new_with_label("Consult our offers");
    button[3] = gtk_button_new_with_label("Contact us");

    gtk_box_pack_start(GTK_BOX(vbox), button[0], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button[1], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button[2], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button[3], TRUE, TRUE, 0);



    //DISPLAY THE WINDOW
    gtk_widget_show_all(window);

    gtk_main();

  return 0;
}
