#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void gtk_box_pack_start(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
void gtk_box_pack_end(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
void gtk_entry_set_visibility(GtkEntry *entry, gboolean visible);
void buttonClicked_Name(GtkWidget *widget, gpointer data);
void buttonClicked_Surname(GtkWidget *widget, gpointer data);
void buttonClicked_Email(GtkWidget *widget, gpointer data);
void buttonClicked_Password(GtkWidget *widget, gpointer data);
void buttonClicked_Password2(GtkWidget *widget, gpointer data);
//static void message_dialog_clicked (GtkButton *validButton, gpointer user_data, GtkWidget *window);
int main(int argc, char *argv[]) {

    int i = 0;
    GtkWidget *window;
    GtkWidget *vbox;

    GtkWidget *toolbar;
    GtkToolItem *sep;
    GtkToolItem *exitTb;
    GtkToolItem *undo;
    GtkWidget *formArray;
    GtkWidget *formName[4];
    GtkEntry *formText[4] = {0};

    GtkWidget *validButton;
    GtkWidget *headerTitleLabel;
    gchar *headerTitle;

    GtkWidget *error;

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

    //THE MAIN BOX
    vbox = gtk_vbox_new(FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    //TOOL BAR MENU
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

    headerTitle = g_locale_from_utf8("\n\n<b><big>Create your account</big></b>\n\n", -1, NULL, NULL, NULL);
    headerTitleLabel = gtk_label_new(headerTitle);
    g_free(headerTitle);
    gtk_label_set_use_markup(GTK_LABEL(headerTitleLabel), TRUE);
    gtk_label_set_justify(GTK_LABEL(headerTitleLabel), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), headerTitleLabel, FALSE, FALSE, 0);

    formArray = gtk_table_new(5, 2, TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), formArray, FALSE, FALSE, 0);
    //NAME
    formName[0] = gtk_label_new("Name");
    formText[0] = gtk_entry_new();

    gtk_table_attach(GTK_TABLE(formArray), formName[0], 0, 1, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(formArray), formText[0], 1, 2, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    //SURNAME
    formName[1] = gtk_label_new("Surname");
    formText[1] = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(formArray), formName[1], 0, 1, 1, 2, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(formArray), formText[1], 1, 2, 1, 2, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    //MAIL
    formName[2] = gtk_label_new("E-mail");
    formText[2] = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(formArray), formName[2], 0, 1, 2, 3, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(formArray), formText[2], 1, 2, 2, 3, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    //PASSWORD
    formName[3] = gtk_label_new("Password");
    formText[3] = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(formText[3]), FALSE); //HIDE PASSWORD
    gtk_entry_set_invisible_char(GTK_ENTRY(formText[3]), '*'); //REPLACE THE CHARACTER BY *
    gtk_table_attach(GTK_TABLE(formArray), formName[3], 0, 1, 3, 4, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(formArray), formText[3], 1, 2, 3, 4, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    //PASSWORD 2
    formName[4] = gtk_label_new("Confirm your password");
    formText[4] = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(formText[4]), FALSE); //HIDE PASSWORD
    gtk_entry_set_invisible_char(GTK_ENTRY(formText[4]), '*'); //REPLACE THE CHARACTER BY *
    gtk_table_attach(GTK_TABLE(formArray), formName[4], 0, 1, 4, 5, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(formArray), formText[4], 1, 2, 4, 5, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    validButton = gtk_button_new_with_label("Create my account");
    gtk_table_attach(GTK_TABLE(formArray), validButton, 1, 2, 5, 6, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    //CALL FUNCTIONS: buttonClicked
    g_signal_connect(validButton, "clicked", G_CALLBACK(buttonClicked_Name), formText[0]);
    g_signal_connect(validButton, "clicked", G_CALLBACK(buttonClicked_Surname), formText[1]);
    g_signal_connect(validButton, "clicked", G_CALLBACK(buttonClicked_Email), formText[2]);
    g_signal_connect(validButton, "clicked", G_CALLBACK(buttonClicked_Password), formText[3]);
    g_signal_connect(validButton, "clicked", G_CALLBACK(buttonClicked_Password2), formText[4]);

    //DISPLAY THE WINDOW
    gtk_widget_show_all(window);

    gtk_main();

  return 0;
}
/** AU CLIC DU BOUTTON, ON RECUPERE LES DONNEES SAISIES **/
void buttonClicked_Name(GtkWidget *widget, gpointer data){

    char *name;
    name = gtk_entry_get_text(GTK_ENTRY(data));
    printf("Name: %s\n", name);

}
void buttonClicked_Surname(GtkWidget *widget, gpointer data){

    char *surname;
    surname = gtk_entry_get_text(GTK_ENTRY(data));
    printf("Surname: %s\n", surname);

}

void buttonClicked_Email(GtkWidget *widget, gpointer data){

    char *email;
    email = gtk_entry_get_text(GTK_ENTRY(data));
    printf("Email: %s\n", email);

}

void buttonClicked_Password(GtkWidget *widget, gpointer data){

    char *password;
    password = gtk_entry_get_text(GTK_ENTRY(data));
    printf("Password2: %s\n", password);

}

void buttonClicked_Password2(GtkWidget *widget, gpointer data){

    char *password2;
    password2 = gtk_entry_get_text(GTK_ENTRY(data));
    printf("Password2: %s\n", password2);

}

