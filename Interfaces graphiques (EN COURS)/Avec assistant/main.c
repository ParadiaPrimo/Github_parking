#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void gtk_box_pack_start(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
void gtk_box_pack_end(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
static void destroySubContents(GtkWidget *widget, gpointer data);
static void destroyAllContent(GtkWidget *widget, gpointer data);
static void mainMenu(GtkApplication* app, gpointer data);
static void registrationForm(GtkWidget *widget, gpointer data);
//From the registration form
void grabAll(GtkWidget *widget, gpointer data, char *name, char *surname, char *email, char *password, char *password2);
int main(int argc, char *argv[]) {

    GtkApplication *app;
    //INITIALIZATION OF GTK
    gtk_init(&argc, &argv);
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE); // <--- remplacer NULL par "***.*****.**" si NULL ne fonctionne pas
    g_signal_connect(app, "activate", G_CALLBACK (mainMenu), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;


  return 0;
}
static void mainMenu(GtkApplication* app, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;

    GtkWidget *toolbar;
    GtkToolItem *sep;
    GtkToolItem *exitTb;

    GtkWidget *buttonArray;
    GtkWidget *buttonLabel;
    GtkWidget *button[5];

    GtkWidget *headerTitleLabel;
    gchar *headerTitle;
    GtkWidget *textLabel;

    GtkWidget *frame;
    GtkWidget *vBoxFrame;
    GtkWidget *scrollbar;

    GdkColor color;
    color.red = 0x00C0;
    color.green = 0x9887;
    color.blue = 0xF888;

    window = gtk_application_window_new (app);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);
    gtk_container_set_border_width(GTK_CONTAINER(window), 30);
    gtk_window_set_title(GTK_WINDOW(window), "PARK'CAR");
    gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);

    printf("I created the window\n");

    //SCROLLBAR
    scrollbar = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window),scrollbar);
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollbar), vbox);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

    toolbar = gtk_toolbar_new();

    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

    sep = gtk_separator_tool_item_new();

    /*gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, 1);

    exitTb = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);

    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exitTb, 2);

    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);
    g_signal_connect(G_OBJECT(exitTb), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);*/

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

    //g_signal_connect(button[0], "clicked", G_CALLBACK(createWindow), NULL);
    //g_signal_connect(button[0], "clicked", G_CALLBACK(destroySubContents), &button);
    g_signal_connect(button[0], "clicked", G_CALLBACK(destroyAllContent), vbox);
    g_signal_connect(button[0], "clicked", G_CALLBACK(registrationForm), scrollbar);
    /*g_signal_connect(button[0], "clicked", G_CALLBACK(destroyAllContent), buttonLabel);
    g_signal_connect(button[0], "clicked", G_CALLBACK(destroyAllContent), buttonArray);
    g_signal_connect(button[0], "clicked", G_CALLBACK(destroyAllContent), textLabel);
    g_signal_connect(button[0], "clicked", G_CALLBACK(destroyAllContent), vBoxFrame);
    g_signal_connect(button[0], "clicked", G_CALLBACK(destroyAllContent), frame);
    g_signal_connect(button[0], "clicked", G_CALLBACK(destroyAllContent), headerTitleLabel);
    g_signal_connect(button[0], "clicked", G_CALLBACK(destroyAllContent), headerTitle);*/

    //DISPLAY THE WINDOW
    gtk_widget_show_all(window);


}

static void destroySubContents(GtkWidget *widget, gpointer data){
    /** This will destroy all buttons **/
    GtkWidget **content = data;
    gtk_widget_destroy(content[0]);
    gtk_widget_destroy(content[1]);
    gtk_widget_destroy(content[2]);
    gtk_widget_destroy(content[3]);
    gtk_widget_destroy(content[4]);
}
static void destroyAllContent(GtkWidget *widget, gpointer data){
    /** This will destroy all boxes and widgets**/
    gtk_widget_destroy(data);

}

static void registrationForm(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;

    GtkWidget *scrollbar;
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
    printf("olala");
    scrollbar = data;

    //THE MAIN BOX
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(scrollbar), vbox);
    //TOOL BAR MENU
    toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

    /*undo = gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), undo, 0);
    sep = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, 1);
    exitTb = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exitTb, 2);

    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);
    g_signal_connect(G_OBJECT(exitTb), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);*/

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
    g_signal_connect(validButton, "clicked", G_CALLBACK(grabAll), &formText);

    //DISPLAY THE WINDOW
    gtk_widget_show_all(window);
}
/** AU CLIC DU BOUTTON, ON RECUPERE LES DONNEES SAISIES **/
void grabAll(GtkWidget *widget, gpointer data, char *name, char *surname, char *email, char *password, char *password2){

    GtkWidget **value = data;
    name = gtk_entry_get_text(GTK_ENTRY(value[0]));
    printf("Name: %s\n", name);
    surname = gtk_entry_get_text(GTK_ENTRY(value[1]));
    printf("Surname: %s\n", surname);
    email = gtk_entry_get_text(GTK_ENTRY(value[2]));
    printf("Email: %s\n", email);
    password = gtk_entry_get_text(GTK_ENTRY(value[3]));
    printf("Password: %s\n", password);
    password2 = gtk_entry_get_text(GTK_ENTRY(value[4]));
    printf("Password2: %s\n", password2);

}
