#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*LES COMMENTAIRES SONT EN FRANCAIS POUR LE MOMENT*/
void gtk_box_pack_start(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
void gtk_box_pack_end(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
static void registrationForm(GtkContainer *vbox, GtkWidget *toolbar);
void gtk_container_empty(GtkContainer *vbox);

int main(int argc, char *argv[]) {

    GtkWidget *window;
    GtkContainer *vbox;
    GtkWidget *hbox;

    GtkWidget *toolbar;
    GtkToolItem *sep;
    GtkToolItem *exitTb;
    GtkWidget *buttonArray;
    GtkWidget *buttonLabel;
    GtkWidget *button[5];

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
    hbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_add(GTK_CONTAINER(window), hbox);

    toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

    sep = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);
    exitTb = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exitTb, -1);

    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);
    g_signal_connect(G_OBJECT(exitTb), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    buttonArray = gtk_table_new(4, 1, TRUE);
    buttonLabel = gtk_label_new(buttonArray);
    gtk_label_set_justify(GTK_LABEL(buttonLabel), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(vbox), buttonArray, FALSE, FALSE, 0);
    button[0] = gtk_button_new_with_label("         Log in          ");
    button[4] = gtk_button_new_with_label("          Sign in        ");
    button[1] = gtk_button_new_with_label("    Check our parking    ");
    button[2] = gtk_button_new_with_label("   Consult our offers    ");
    button[3] = gtk_button_new_with_label(" Book your parking space ");

    gtk_table_attach(GTK_TABLE(buttonArray), button[0], 3, 4, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(buttonArray), button[1], 3, 4, 1, 2, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(buttonArray), button[2], 3, 4, 2, 3, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(buttonArray), button[3], 3, 4, 3, 4, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(buttonArray), button[4], 3, 4, 4, 5, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    g_signal_connect(G_OBJECT(button[0]), "clicked", G_CALLBACK(registrationForm), NULL);

    //DISPLAY THE WINDOW
    gtk_widget_show_all(window);

    gtk_main();

  return 0;
}
void gtk_container_empty(GtkContainer *vbox){
    GList * children = gtk_container_get_children(vbox);
    while(children){
        gtk_widget_destroy(children->data);
        children = g_list_next(children);
    }
    g_list_free(children);
}
static void registrationForm(GtkContainer *vbox, GtkWidget *toolbar){
    int i;
    GtkWidget *formArray;
    GtkWidget *formName[5];
    GtkWidget *formText[5];
    GtkWidget *undo;


    gtk_container_empty(GTK_CONTAINER(vbox));

    undo = gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), undo, 0);

    formArray = gtk_table_new(5, 2, TRUE);

    //NAME
    formName[0] = gtk_label_new("Name");
    formText[0] = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(formArray), formName[0], 0, 1, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(formArray), formText[0], 1, 2, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
    printf("ok");
    //SURNAME
    formName[1] = gtk_label_new("Surname");
    formText[1] = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(formArray), formName[1], 0, 1, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(formArray), formText[1], 1, 2, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
    //ADDRESS
    formName[2] = gtk_label_new("Address");
    formText[2] = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(formArray), formName[2], 0, 1, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(formArray), formText[2], 1, 2, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
    //PASSWORD
    formName[3] = gtk_label_new("Password");
    formText[3] = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(formArray), formName[3], 0, 1, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(formArray), formText[3], 1, 2, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
    //PASSWORD 2
    formName[4] = gtk_label_new("Confirm your password");
    formText[4] = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(formArray), formName[4], 0, 1, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(formArray), formText[4], 1, 2, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
}
