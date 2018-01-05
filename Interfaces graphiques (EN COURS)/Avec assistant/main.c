#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void gtk_box_pack_start(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
void gtk_box_pack_end(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
static void destroySubContents(GtkWidget *widget, gpointer data);
static void destroyAllContent(GtkWidget *widget, gpointer data);
static void mainMenu(GtkApplication* app, gpointer data);
static void logIn(GtkButton *button, gpointer data);
static void registrationForm(GtkWidget *widget, gpointer data);
static void doReservation(GtkWidget *widget, gpointer data);
static void checkConnetion(GtkWidget *widget, gpointer data, char *email, char *password);
static void grabAll_Reservation(GtkWidget *spinner, gpointer data, int *day, int *month, int *year, int *hour, int *minute, int *day2, int *month2, int *year2, int *hour2, int *minute2);
void buttonClicked_Reservation(GtkWidget *widget, gpointer data);
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

    button[0] = gtk_button_new_with_label("         Sign in          ");
    button[1] = gtk_button_new_with_label("          Log in        ");
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


    g_signal_connect(G_OBJECT(button[0]), "clicked", G_CALLBACK(registrationForm), NULL);
    //g_signal_connect(G_OBJECT(button[0]), "clicked", G_CALLBACK(destroyAllContent), (GtkWidget*)window);

    g_signal_connect(G_OBJECT(button[1]), "clicked", G_CALLBACK(logIn), NULL);

    g_signal_connect(G_OBJECT(button[4]), "clicked", G_CALLBACK(doReservation), NULL);


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

    /** This will destroy all boxes and widgets **/
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
static void logIn(GtkButton *button, gpointer data){

    GtkWidget *window = NULL;
    GtkWidget *content_area;
    GtkWidget *dialog;
    GtkWidget *hbox;
    GtkWidget *stock;
    GtkWidget *table;
    GtkWidget *entry[2];
    GtkWidget *label;
    gint response;

    dialog = gtk_dialog_new_with_buttons("PARK'CAR - Sign In", GTK_WINDOW(window), GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT, GTK_STOCK_OK, GTK_RESPONSE_OK, NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 8);
    gtk_container_set_border_width (GTK_CONTAINER (hbox), 8);
    gtk_box_pack_start (GTK_BOX(content_area), hbox, FALSE, FALSE, 0);

    stock = gtk_image_new_from_stock(GTK_STOCK_DIALOG_AUTHENTICATION, GTK_ICON_SIZE_DIALOG);
    gtk_box_pack_start (GTK_BOX(hbox), stock, FALSE, FALSE, 0);

    table = gtk_grid_new ();
    gtk_grid_set_row_spacing(GTK_GRID(table), 4);
    gtk_grid_set_column_spacing(GTK_GRID(table), 4);
    gtk_box_pack_start(GTK_BOX(hbox), table, TRUE, TRUE, 0);

    label = gtk_label_new_with_mnemonic("Your email");
    gtk_grid_attach (GTK_GRID(table), label, 0, 0, 1, 1);
    entry[0] = gtk_entry_new();
    gtk_grid_attach (GTK_GRID(table), entry[0], 1, 0, 1, 1);
    gtk_label_set_mnemonic_widget(GTK_LABEL (label), entry[0]);

    label = gtk_label_new_with_mnemonic("Your password");
    gtk_grid_attach (GTK_GRID (table), label, 0, 1, 1, 1);
    entry[1] = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry[1]), FALSE); //HIDE PASSWORD
    gtk_entry_set_invisible_char(GTK_ENTRY(entry[1]), '*'); //REPLACE THE CHARACTER BY *
    gtk_grid_attach (GTK_GRID(table), entry[1], 1, 1, 1, 1);
    gtk_label_set_mnemonic_widget (GTK_LABEL (label), entry[1]);

    gtk_widget_show_all(hbox);
    response = gtk_dialog_run(GTK_DIALOG(dialog));
    /** If the button "OK" is clicked, do callback **/
    if(response == GTK_RESPONSE_OK){
        printf("Button clicked!\n %d", response);
        g_signal_connect(G_OBJECT(GTK_RESPONSE_OK), "activate", G_CALLBACK(checkConnetion), &entry);
    }

}

static void checkConnetion(GtkWidget *widget, gpointer data, char *email, char *password){

    GtkWidget **value = data;
    email = gtk_entry_get_text(GTK_ENTRY(value[0]));
    printf("Email: %s\n", email);
    password = gtk_entry_get_text(GTK_ENTRY(value[1]));
    printf("Password: %s\n", password);


    /** All checks, if invalid response = 0 **/
}
static void doReservation(GtkWidget *widget, gpointer data){
    int i = 0;
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *vbox2;
    GtkWidget *vbox3;

    GtkWidget *hbox;
    GtkWidget *scrollbar;

    GtkWidget *toolbar;
    GtkToolItem *sep;
    GtkToolItem *exitTb;
    GtkToolItem *undo;

    GtkWidget *formArray;
    GtkWidget *formName;
    GtkWidget *formText;

    GtkWidget *validButton;
    GtkWidget *headerTitleLabel;
    gchar *headerTitle;
    GtkWidget *textLabel;
    gchar *text;

    GtkWidget *error;

    GtkWidget *frame;
    GtkWidget *vBoxFrame;

    GtkWidget *box, *combo;
    GtkWidget *spinner[9];
    GtkAdjustment *adj;


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

    headerTitle = g_locale_from_utf8("\n\n<b><big>Book your parking space</big></b>\n\n", -1, NULL, NULL, NULL);
    headerTitleLabel = gtk_label_new(headerTitle);
    g_free(headerTitle);
    gtk_label_set_use_markup(GTK_LABEL(headerTitleLabel), TRUE);
    gtk_label_set_justify(GTK_LABEL(headerTitleLabel), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), headerTitleLabel, FALSE, FALSE, 0);

    frame = gtk_frame_new("Location");
    gtk_box_pack_start(GTK_BOX(vbox), frame, FALSE, FALSE, 5);

    vBoxFrame = gtk_vbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(frame), vBoxFrame);
    textLabel = gtk_label_new("Place des 5 Martyrs du Lycee Buffon\n75015 PARIS\n");
    gtk_box_pack_start(GTK_BOX(vBoxFrame), textLabel, FALSE, FALSE, 10);

    frame = gtk_frame_new("Specify your dates - From");
    gtk_box_pack_start(GTK_BOX(vbox), frame, FALSE, FALSE, 0);


        vbox2 = gtk_vbox_new (FALSE, 0);
        gtk_container_set_border_width (GTK_CONTAINER (vbox2), 10);
        gtk_container_add (GTK_CONTAINER(frame), vbox2);

        hbox = gtk_hbox_new (FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox2), hbox, FALSE, FALSE, 10);

        vbox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX (hbox), vbox3, FALSE, FALSE, 10);

        /**         BEGIN       **/
        //DAY
        textLabel = gtk_label_new ("Day");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (vbox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(1.0, 1.0, 31.0, 1.0, 5.0, 0.0);
        spinner[0] = gtk_spin_button_new(adj, 1.0, 0);
        //g_signal_connect(spinner[0], "value-changed", G_CALLBACK(grabDay), NULL);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[0]), TRUE);
        gtk_box_pack_start (GTK_BOX (vbox3), spinner[0], FALSE, TRUE, 10);

        vbox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX(hbox), vbox3, FALSE, FALSE, 10);

        //MONTH
        textLabel = gtk_label_new ("Month");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (vbox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(1.0, 1.0, 12.0, 1.0, 5.0, 0.0);
        spinner[1] = gtk_spin_button_new(adj, 0, 0);
        //g_signal_connect(spinner[1], "value-changed", G_CALLBACK(grabMonth), NULL);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[1]), TRUE);
        gtk_box_pack_start (GTK_BOX (vbox3), spinner[1], FALSE, TRUE, 10);

        vbox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX(hbox), vbox3, FALSE, FALSE, 10);
        /*//MONTH
        textLabel = gtk_label_new ("Month");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start(GTK_BOX(vbox3), textLabel, FALSE, FALSE, 10);
        box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_size_request(box, 50, 0);
        //gtk_container_set_border_width(GTK_CONTAINER(box), 60);
        gtk_box_pack_start (GTK_BOX (vbox2), box, FALSE, FALSE, 10);

        combo = gtk_combo_box_text_new();
        fill_combo_entry_month(combo);
        gtk_container_add(GTK_CONTAINER(box), combo);

        vbox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX (hbox), vbox3, FALSE, FALSE, 10);*/

        //YEAR
        textLabel = gtk_label_new ("Year");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start(GTK_BOX(vbox3), textLabel, FALSE, TRUE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(1.0, 2018.0, 2030.0, 1.0, 5.0, 0.0);
        spinner[2] = gtk_spin_button_new(adj, 0, 0);
        //g_signal_connect(spinner[2], "value-changed", G_CALLBACK(grabYear), NULL);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[2]), FALSE);
        //gtk_widget_set_size_request (spinner, 55, -1);
        gtk_box_pack_start (GTK_BOX (vbox3), spinner[2], FALSE, TRUE, 10);

        vbox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX (hbox), vbox3, FALSE, FALSE, 10);

        //TIME
            //HOUR
        textLabel = gtk_label_new ("Hour");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (vbox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(0.0, 0.0, 23.0, 1.0, 5.0, 0.0);
        spinner[3] = gtk_spin_button_new(adj, 0, 0);
        //g_signal_connect(spinner[3], "value-changed", G_CALLBACK(grabHour), NULL);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[3]), TRUE);
        gtk_box_pack_start(GTK_BOX (vbox3), spinner[3], FALSE, TRUE, 10);

        vbox3 = gtk_vbox_new(FALSE, 0);
        gtk_box_pack_start (GTK_BOX(hbox), vbox3, FALSE, FALSE, 10);
            //MINUTE
        gtk_box_pack_start (GTK_BOX(hbox), vbox3, FALSE, FALSE, 10);
        textLabel = gtk_label_new ("Minute");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (vbox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(0.0, 0.0, 59.0, 1.0, 5.0, 0.0);
        spinner[4] = gtk_spin_button_new(adj, 0, 0);
        //g_signal_connect(spinner[4], "value-changed", G_CALLBACK(grabMinute), NULL);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[4]), TRUE);
        gtk_box_pack_start(GTK_BOX (vbox3), spinner[4], FALSE, TRUE, 10);


    frame = gtk_frame_new("Specify your dates - To");
    gtk_box_pack_start(GTK_BOX(vbox), frame, FALSE, FALSE, 0);

        vbox2 = gtk_vbox_new (FALSE, 0);
        gtk_container_set_border_width (GTK_CONTAINER (vbox2), 10);
        gtk_container_add (GTK_CONTAINER(frame), vbox2);

        hbox = gtk_hbox_new (FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox2), hbox, FALSE, FALSE, 10);

        vbox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX (hbox), vbox3, FALSE, FALSE, 10);

        /**         END       **/
        //DAY
        textLabel = gtk_label_new ("Day");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (vbox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(1.0, 1.0, 31.0, 1.0, 5.0, 0.0);
        spinner[5] = gtk_spin_button_new(adj, 0, 0);
        //g_signal_connect(spinner[5], "value-changed", G_CALLBACK(grabDay), NULL);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[5]), TRUE);
        gtk_box_pack_start (GTK_BOX (vbox3), spinner[5], FALSE, TRUE, 10);

        vbox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX(hbox), vbox3, FALSE, FALSE, 10);

        //MONTH
        textLabel = gtk_label_new ("Month");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (vbox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(1.0, 1.0, 12.0, 1.0, 5.0, 0.0);
        spinner[6] = gtk_spin_button_new(adj, 1.0, 0);
        //g_signal_connect(spinner[6], "value-changed", G_CALLBACK(grabDay), NULL);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[6]), TRUE);
        gtk_box_pack_start (GTK_BOX (vbox3), spinner[6], FALSE, TRUE, 10);

        vbox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX(hbox), vbox3, FALSE, FALSE, 10);

        //YEAR
        textLabel = gtk_label_new ("Year");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start(GTK_BOX(vbox3), textLabel, FALSE, TRUE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(1.0, 2018.0, 2030.0, 1.0, 5.0, 0.0);
        spinner[7] = gtk_spin_button_new(adj, 0, 0);
        //g_signal_connect(spinner[7], "value-changed", G_CALLBACK(grabDay), NULL);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[7]), FALSE);
        gtk_box_pack_start (GTK_BOX (vbox3), spinner[7], FALSE, TRUE, 10);
        vbox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX(hbox), vbox3, FALSE, FALSE, 10);
        //TIME
            //HOUR
        textLabel = gtk_label_new ("Hour");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (vbox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(0.0, 0.0, 23.0, 1.0, 5.0, 0.0);
        spinner[8] = gtk_spin_button_new(adj, 0, 0);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[8]), TRUE);
        gtk_box_pack_start(GTK_BOX (vbox3), spinner[8], FALSE, TRUE, 10);

        vbox3 = gtk_vbox_new(FALSE, 0);
        gtk_box_pack_start (GTK_BOX(hbox), vbox3, FALSE, FALSE, 10);
            //MINUTE
        gtk_box_pack_start (GTK_BOX(hbox), vbox3, FALSE, FALSE, 10);
        textLabel = gtk_label_new ("Minute");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (vbox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(0.0, 0.0, 59.0, 1.0, 5.0, 0.0);
        spinner[9] = gtk_spin_button_new(adj, 0, 0);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[9]), TRUE);
        gtk_box_pack_start(GTK_BOX (vbox3), spinner[9], FALSE, TRUE, 10);


    formArray = gtk_table_new(5, 2, TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), formArray, FALSE, FALSE, 10);
    //LICENSE PLATE
    formName = gtk_label_new("Enter your car registration");
    formText = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(formArray), formName, 0, 1, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(formArray), formText, 1, 2, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);


    validButton = gtk_button_new_with_label("Book my parking space");
    gtk_table_attach(GTK_TABLE(formArray), validButton, 1, 2, 1, 2, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    //g_signal_connect(validButton, "clicked", G_CALLBACK(buttonClicked), combo);
    g_signal_connect(validButton, "clicked", G_CALLBACK(grabAll), &spinner);


    //DISPLAY THE WINDOW
    gtk_widget_show_all(window);

    gtk_main();
}
void buttonClicked_Reservation(GtkWidget *widget, gpointer data){

    //CAR REGISTRATION
    char *carRegistration;
    carRegistration = gtk_entry_get_text(GTK_ENTRY(data));
    printf("\n%s", carRegistration);

}
static void grabAll_Reservation(GtkWidget *spinner, gpointer data, int *day, int *month, int *year, int *hour, int *minute, int *day2, int *month2, int *year2, int *hour2, int *minute2){

    GtkSpinButton **value = data;
    /** FROM **/
    day = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(value[0]));
    month = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(value[1]));
    year = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(value[2]));
    hour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(value[3]));
    minute = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(value[4]));
    printf("\nFROM:\nDay: %d\nMonth: %d\nYear: %d\nAt %d:%d", day, month, year, hour, minute);
    /** TO **/
    day2 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(value[5]));
    month2 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(value[6]));
    year2 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(value[7]));
    hour2 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(value[8]));
    minute2 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(value[9]));

    printf("\n\nTO:\nDay: %d\nMonth: %d\nYear: %d\nAt %d:%d", day2, month2, year2, hour2, minute2);


}

/** FONCTIONS UTILES **/
//void gtk_entry_set_max_length(GtkEntry *entry, gint max); Définit le nombre maximum de caractère que l'utilisateur peut saisir.
//gint gtk_entry_get_max_length(GtkEntry *entry); Récupère le nombre maximum de caractère que l'utilisateur peut saisir.
