#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include <winsock.h>
//#include <MYSQL/mysql.h>
//#include <winsock2.h>
//#include "clientParking.h"
static void grabPaymentData(GtkWidget *widget, gpointer data);
static void messageSuccessPayment();
static void messageSubscriptionChosen();
static void messageErrorInvalidCC();
static void messageSuccessCancelled();
static void messageErrorPassword();
static void messageErrorConnection();
static void messageSuccess();
static void grabEntryData(GtkWidget *widget, gpointer data);
static void messageError();
static void messageErrorCar();
static void grabCarId(GtkWidget *widget, gpointer data);
static void grabRegistrationFormData(GtkWidget *widget, gpointer data, char *name, char *surname, char *email, char *password, char *password2);
static void grabReservationData(GtkWidget *spinner, gpointer data, int *day, int *month, int *year, int *hour, int *minute, int *day2, int *month2, int *year2, int *hour2, int *minute2, int *fuel, int *carWashInside, int *carWashOutside, int *carWashTotal);
int toggledFunction(GtkWidget *widget, gpointer data);

int main(int argc, char **argv){


    GtkWidget *window;
    GtkWidget *notebook;
    //ALL BOXES/CONTAINERS
    GtkWidget *vBox;
    GtkWidget *subvBox;

    GtkWidget *scrollbar;
    //LABEL NOTEBOOK
    GtkWidget *pTabLabel;
    gchar *sTabLabel;
    //TITLE
    GtkWidget *headerTitleLabel;
    gchar *headerTitle;
    //FORM
    GtkWidget *formArray;
    GtkWidget *formName[4];
    GtkEntry *formText[4] = {0};
    //BUTTON
    GtkWidget *validButton;

    gint i = 0;

    //INITIALIZATION OF GTK
    gtk_init(&argc,&argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "PARK'CAR");
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    vBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vBox);

    /* Creation du GtkNotebook */
    notebook = gtk_notebook_new();
    gtk_box_pack_start(GTK_BOX(vBox), notebook, TRUE, TRUE, 0);
    /* Position des onglets : en bas */
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);
    /* Ajout des boutons de navigation */
    gtk_notebook_set_scrollable(GTK_NOTEBOOK(notebook), TRUE);

    subvBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), subvBox);
    headerTitle = g_locale_from_utf8("\n\n<b><big>Create your account</big></b>\n\n", -1, NULL, NULL, NULL);
    headerTitleLabel = gtk_label_new(headerTitle);

    gtk_label_set_use_markup(GTK_LABEL(headerTitleLabel), TRUE);
    gtk_label_set_justify(GTK_LABEL(headerTitleLabel), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(subvBox), headerTitleLabel, FALSE, FALSE, 0);

    formArray = gtk_table_new(5, 2, TRUE);
    gtk_box_pack_start(GTK_BOX(subvBox), formArray, FALSE, FALSE, 0);

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
    g_signal_connect(validButton, "clicked", G_CALLBACK(grabRegistrationFormData), &formText);


    sTabLabel = g_strdup_printf("Sign in");
    pTabLabel = gtk_label_new(sTabLabel);

    /* Insertion de la page */
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), subvBox, pTabLabel);

    /** PAGE 2 **/

    GtkWidget *vBox2;
    GtkWidget *subvBox2;
    GtkWidget *subvBox3;
    GtkWidget *hbox;
    GtkWidget *arrayText;
    GtkWidget *subText[3];
    GtkWidget *textLabel;
    gchar *text;

    GtkWidget *frame;
    GtkWidget *vBoxFrame;

    GtkWidget *box, *combo;
    GtkWidget *spinner[11];

    GtkAdjustment *adj;

    //SCROLLBAR
    scrollbar = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(vBox),scrollbar);
    vBox = gtk_vbox_new(FALSE, 0);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollbar), vBox);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

    vBox2 = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(scrollbar), vBox2);
    headerTitle = g_locale_from_utf8("\n\n<b><big>Book your parking space</big></b>\n\n", -1, NULL, NULL, NULL);
    headerTitleLabel = gtk_label_new(headerTitle);
    gtk_label_set_use_markup(GTK_LABEL(headerTitleLabel), TRUE);
    gtk_label_set_justify(GTK_LABEL(headerTitleLabel), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vBox2), headerTitleLabel, FALSE, FALSE, 0);

    frame = gtk_frame_new("Location");
    gtk_box_pack_start(GTK_BOX(vBox2), frame, FALSE, FALSE, 5);

    vBoxFrame = gtk_vbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(frame), vBoxFrame);
    textLabel = gtk_label_new("Place des 5 Martyrs du Lycee Buffon\n75015 PARIS\n");
    gtk_box_pack_start(GTK_BOX(vBoxFrame), textLabel, FALSE, FALSE, 10);

    frame = gtk_frame_new("Specify your dates - From");
    gtk_box_pack_start(GTK_BOX(vBox2), frame, FALSE, FALSE, 0);


        subvBox2 = gtk_vbox_new (FALSE, 0);
        gtk_container_set_border_width (GTK_CONTAINER (subvBox2), 10);
        gtk_container_add (GTK_CONTAINER(frame), subvBox2);

        hbox = gtk_hbox_new (FALSE, 0);
        gtk_box_pack_start(GTK_BOX(subvBox2), hbox, FALSE, FALSE, 10);

        subvBox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX (hbox), subvBox3, FALSE, FALSE, 10);

        /**         BEGIN       **/
        //DAY
        textLabel = gtk_label_new ("Day");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (subvBox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(1.0, 1.0, 31.0, 1.0, 5.0, 0.0);
        spinner[0] = gtk_spin_button_new(adj, 1.0, 0);
        //g_signal_connect(spinner[0], "value-changed", G_CALLBACK(grabDay), NULL);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[0]), TRUE);
        gtk_box_pack_start (GTK_BOX (subvBox3), spinner[0], FALSE, TRUE, 10);

        subvBox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX(hbox), subvBox3, FALSE, FALSE, 10);

        //MONTH
        textLabel = gtk_label_new ("Month");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (subvBox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(1.0, 1.0, 12.0, 1.0, 5.0, 0.0);
        spinner[1] = gtk_spin_button_new(adj, 0, 0);
        //g_signal_connect(spinner[1], "value-changed", G_CALLBACK(grabMonth), NULL);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[1]), TRUE);
        gtk_box_pack_start (GTK_BOX (subvBox3), spinner[1], FALSE, TRUE, 10);

        subvBox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX(hbox), subvBox3, FALSE, FALSE, 10);


        //YEAR
        textLabel = gtk_label_new ("Year");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start(GTK_BOX(subvBox3), textLabel, FALSE, TRUE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(1.0, 2018.0, 2030.0, 1.0, 5.0, 0.0);
        spinner[2] = gtk_spin_button_new(adj, 0, 0);
        //g_signal_connect(spinner[2], "value-changed", G_CALLBACK(grabYear), NULL);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[2]), FALSE);
        //gtk_widget_set_size_request (spinner, 55, -1);
        gtk_box_pack_start (GTK_BOX (subvBox3), spinner[2], FALSE, TRUE, 10);

        subvBox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX (hbox), subvBox3, FALSE, FALSE, 10);

        //TIME
            //HOUR
        textLabel = gtk_label_new ("Hour");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (subvBox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(0.0, 0.0, 23.0, 1.0, 5.0, 0.0);
        spinner[3] = gtk_spin_button_new(adj, 0, 0);
        //g_signal_connect(spinner[3], "value-changed", G_CALLBACK(grabHour), NULL);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[3]), TRUE);
        gtk_box_pack_start(GTK_BOX (subvBox3), spinner[3], FALSE, TRUE, 10);

        subvBox3 = gtk_vbox_new(FALSE, 0);
        gtk_box_pack_start (GTK_BOX(hbox), subvBox3, FALSE, FALSE, 10);
            //MINUTE
        gtk_box_pack_start (GTK_BOX(hbox), subvBox3, FALSE, FALSE, 10);
        textLabel = gtk_label_new ("Minute");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (subvBox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(0.0, 0.0, 59.0, 1.0, 5.0, 0.0);
        spinner[4] = gtk_spin_button_new(adj, 0, 0);
        //g_signal_connect(spinner[4], "value-changed", G_CALLBACK(grabMinute), NULL);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[4]), TRUE);
        gtk_box_pack_start(GTK_BOX (subvBox3), spinner[4], FALSE, TRUE, 10);


    frame = gtk_frame_new("Specify your dates - To");
    gtk_box_pack_start(GTK_BOX(vBox2), frame, FALSE, FALSE, 0);

        subvBox2 = gtk_vbox_new (FALSE, 0);
        gtk_container_set_border_width (GTK_CONTAINER (subvBox2), 10);
        gtk_container_add (GTK_CONTAINER(frame), subvBox2);

        hbox = gtk_hbox_new (FALSE, 0);
        gtk_box_pack_start(GTK_BOX(subvBox2), hbox, FALSE, FALSE, 10);

        subvBox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX (hbox), subvBox3, FALSE, FALSE, 10);

        /**         END       **/
        //DAY
        textLabel = gtk_label_new ("Day");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (subvBox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(1.0, 1.0, 31.0, 1.0, 5.0, 0.0);
        spinner[5] = gtk_spin_button_new(adj, 0, 0);

        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[5]), TRUE);
        gtk_box_pack_start (GTK_BOX (subvBox3), spinner[5], FALSE, TRUE, 10);

        subvBox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX(hbox), subvBox3, FALSE, FALSE, 10);

        //MONTH
        textLabel = gtk_label_new ("Month");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (subvBox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(1.0, 1.0, 12.0, 1.0, 5.0, 0.0);
        spinner[6] = gtk_spin_button_new(adj, 1.0, 0);
        //g_signal_connect(spinner[6], "value-changed", G_CALLBACK(grabDay), NULL);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[6]), TRUE);
        gtk_box_pack_start (GTK_BOX (subvBox3), spinner[6], FALSE, TRUE, 10);

        subvBox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX(hbox), subvBox3, FALSE, FALSE, 10);

        //YEAR
        textLabel = gtk_label_new ("Year");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start(GTK_BOX(subvBox3), textLabel, FALSE, TRUE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(1.0, 2018.0, 2030.0, 1.0, 5.0, 0.0);
        spinner[7] = gtk_spin_button_new(adj, 0, 0);

        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[7]), FALSE);
        gtk_box_pack_start (GTK_BOX (subvBox3), spinner[7], FALSE, TRUE, 10);
        subvBox3 = gtk_vbox_new (FALSE, 0);
        gtk_box_pack_start (GTK_BOX(hbox), subvBox3, FALSE, FALSE, 10);
        //TIME
            //HOUR
        textLabel = gtk_label_new ("Hour");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (subvBox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(0.0, 0.0, 23.0, 1.0, 5.0, 0.0);
        spinner[8] = gtk_spin_button_new(adj, 0, 0);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[8]), TRUE);
        gtk_box_pack_start(GTK_BOX (subvBox3), spinner[8], FALSE, TRUE, 10);

        subvBox3 = gtk_vbox_new(FALSE, 0);
        gtk_box_pack_start (GTK_BOX(hbox), subvBox3, FALSE, FALSE, 10);
            //MINUTE
        gtk_box_pack_start (GTK_BOX(hbox), subvBox3, FALSE, FALSE, 10);
        textLabel = gtk_label_new ("Minute");
        gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
        gtk_box_pack_start (GTK_BOX (subvBox3), textLabel, FALSE, FALSE, 10);

        adj = (GtkAdjustment *)gtk_adjustment_new(0.0, 0.0, 59.0, 1.0, 5.0, 0.0);
        spinner[9] = gtk_spin_button_new(adj, 0, 0);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[9]), TRUE);
        gtk_box_pack_start(GTK_BOX (subvBox3), spinner[9], FALSE, TRUE, 10);


    frame = gtk_frame_new("Options");
    gtk_box_pack_start(GTK_BOX(vBox2), frame, FALSE, FALSE, 0);
    subvBox2 = gtk_vbox_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (subvBox2), 10);
    gtk_container_add (GTK_CONTAINER(frame), subvBox2);

    hbox = gtk_hbox_new (FALSE, 0);
    gtk_box_pack_start(GTK_BOX(subvBox2), hbox, FALSE, FALSE, 10);

    subvBox3 = gtk_vbox_new (FALSE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), subvBox3, FALSE, FALSE, 10);
    subvBox2 = gtk_vbox_new (FALSE, 0);

    //FUEL
    textLabel = gtk_label_new ("Fuel (per liter)");
    gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
    gtk_box_pack_start (GTK_BOX (subvBox3), textLabel, FALSE, FALSE, 10);
    adj = (GtkAdjustment *)gtk_adjustment_new(0.0, 0.0, 60.0, 1.0, 5.0, 0.0);

    spinner[10] = gtk_spin_button_new(adj, 0, 0);
    gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[10]), TRUE);
    gtk_box_pack_start (GTK_BOX (subvBox3), spinner[10], FALSE, TRUE, 10);

    subvBox3 = gtk_vbox_new (FALSE, 0);
    gtk_box_pack_start (GTK_BOX(hbox), subvBox3, FALSE, FALSE, 10);

    textLabel = gtk_label_new ("Car wash\n\t1 - Outside\n\t2 - Inside\n\t3 - Both");
    gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);
    gtk_box_pack_start (GTK_BOX (subvBox3), textLabel, FALSE, FALSE, 10);
    adj = (GtkAdjustment *)gtk_adjustment_new(0.0, 0.0, 3.0, 1.0, 5.0, 0.0);

    spinner[11] = gtk_spin_button_new(adj, 0, 0);
    gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinner[11]), TRUE);
    gtk_box_pack_start (GTK_BOX (subvBox3), spinner[11], FALSE, TRUE, 10);

    subvBox3 = gtk_vbox_new (FALSE, 0);
    gtk_box_pack_start (GTK_BOX(hbox), subvBox3, FALSE, FALSE, 10);


    formArray = gtk_table_new(2, 2, TRUE);
    gtk_box_pack_start(GTK_BOX(subvBox3), formArray, FALSE, FALSE, 10);
    textLabel = gtk_label_new ("Credit Card Number (XXXX_XXXX_XXXX_XXXX)");
    subText[0] = gtk_entry_new();

    gtk_table_attach(GTK_TABLE(formArray), textLabel, 1, 2, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(formArray), subText[0], 2, 3, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    textLabel = gtk_label_new ("Credit Card CVC (XXX)");
    gtk_misc_set_alignment(GTK_MISC (textLabel), 0, 0.5);

    subText[1] = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(formArray), textLabel, 1, 2, 1, 2, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(formArray), subText[1], 2, 3, 1, 2, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    subvBox3 = gtk_vbox_new (FALSE, 0);


    formArray = gtk_table_new(5, 2, TRUE);
    gtk_box_pack_start(GTK_BOX(vBox2), formArray, FALSE, FALSE, 10);
    //LICENSE PLATE
    arrayText = gtk_label_new("Enter your car registration");
    subText[2] = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(formArray), arrayText, 0, 1, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(formArray), subText[2], 1, 2, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    validButton = gtk_button_new_with_label("Book my parking space");
    gtk_table_attach(GTK_TABLE(formArray), validButton, 1, 2, 1, 2, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    g_signal_connect(validButton, "clicked", G_CALLBACK(grabReservationData), &spinner); //ALL CONTENTS FROM SPINNERS

    //g_signal_connect(validButton, "clicked", G_CALLBACK(grabCarId), subText);
    sTabLabel = g_strdup_printf("Book your parking space");
    pTabLabel = gtk_label_new(sTabLabel);

    /* Insertion de la page */
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vBox2, pTabLabel);

    /** PAGE 3 **/

    GtkWidget *vBox3;
    GtkWidget *subvBox3b;
    GtkWidget *paned;
    GtkHPaned *hPaned;
    GtkWidget *boxArray;
    GtkWidget *subBox3[5];

    GtkWidget *subTitleLabel[3];
    gchar *subTitle[3];

    vBox3 = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vBox3);
    headerTitle = g_locale_from_utf8("\n\n<b><big>Consult our offers</big></b>\n\n", -1, NULL, NULL, NULL);
    headerTitleLabel = gtk_label_new(headerTitle);
    gtk_label_set_use_markup(GTK_LABEL(headerTitleLabel), TRUE);
    gtk_label_set_justify(GTK_LABEL(headerTitleLabel), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(vBox3), headerTitleLabel, FALSE, FALSE, 0);
    frame = gtk_frame_new("Our subscriptions");
    gtk_box_pack_start(GTK_BOX(vBox3), frame, FALSE, FALSE, 0);
    subvBox3b = gtk_vbox_new(FALSE, 0);

    gtk_container_add(GTK_CONTAINER(frame), subvBox3b);

    boxArray = gtk_table_new(5, 12, FALSE);
    gtk_box_pack_start(GTK_BOX(subvBox3b), boxArray, FALSE, FALSE, 0);

    i = 0;
    for(i = 0; i < 5; i++){
        subBox3[i] = gtk_vbox_new(FALSE, 0);
    }

    subTitle[0] = g_locale_from_utf8("\n<span>Classic</span>\n\n<span>29,99 euros</span><sup>   per month</sup>\n"
                                     "\n\n\n\n<span>With this subscription, you can:\n\n Park your car (3 euros /hour)\nCar wash \n\tInside: 20 euros\n\tOutsite: 25 euros\n\tBoth: 35 euros\nFilling up the gas tank (1,20 /L)</span>", -1, NULL, NULL, NULL);
    subTitleLabel[0] = gtk_label_new(subTitle[0]);
    gtk_label_set_use_markup(GTK_LABEL(subTitleLabel[0]), TRUE);
    gtk_label_set_justify(GTK_LABEL(subTitleLabel[0]), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start(GTK_BOX(subBox3[0]), subTitleLabel[0], FALSE, FALSE, 0);

    gtk_table_attach(GTK_TABLE(boxArray), subBox3[0], 2, 3, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    subTitle[1] = g_locale_from_utf8("\n<span>Premium</span>\n\n<span>46,99 euros</span><sup>   per month</sup>\n"
                                     "\n\n\n\n<span>With this subscription, you can:\n\n Park your car (1 euros /hour)\nCar wash \n\tInside: 10 euros\n\tOutsite: 15 euros\n\tBoth: 20 euros\nFilling up the gas tank (0,90 /L)</span>", -1, NULL, NULL, NULL);
    subTitleLabel[1] = gtk_label_new(subTitle[1]);
    gtk_label_set_use_markup(GTK_LABEL(subTitleLabel[1]), TRUE);
    gtk_label_set_justify(GTK_LABEL(subTitleLabel[1]), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start(GTK_BOX(subBox3[1]), subTitleLabel[1], FALSE, FALSE, 0);

    gtk_table_attach(GTK_TABLE(boxArray), subBox3[1], 3, 4, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    subTitle[2] = g_locale_from_utf8("\n<span>Premium Plus</span>\n\n<span>78,99 euros</span><sup>   per month</sup>\n"
                                     "\n\n\n\n<span>With this subscription, you can:\n\n Park your car (1 euros /hour)\nCar wash \n\tInside: 10 euros\n\tOutsite: 15 euros\n\tBoth: 20 euros\nFilling up the gas tank (0,70 /L)</span>", -1, NULL, NULL, NULL);
    subTitleLabel[2] = gtk_label_new(subTitle[2]);
    gtk_label_set_use_markup(GTK_LABEL(subTitleLabel[2]), TRUE);
    gtk_label_set_justify(GTK_LABEL(subTitleLabel[2]), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start(GTK_BOX(subBox3[2]), subTitleLabel[2], FALSE, FALSE, 0);

    gtk_table_attach(GTK_TABLE(boxArray), subBox3[2], 5, 6, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    GtkWidget *radio1, *radio2, *radio3;
    GtkWidget *grid;
    int subValue;
    subTitle[3] = g_locale_from_utf8("\n<span>Choose the subscription that works for you</span>", -1, NULL, NULL, NULL);
    subTitleLabel[3] = gtk_label_new(subTitle[3]);
    gtk_label_set_use_markup(GTK_LABEL(subTitleLabel[3]), TRUE);
    gtk_label_set_justify(GTK_LABEL(subTitleLabel[3]), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start(GTK_BOX(subBox3[3]), subTitleLabel[3], FALSE, FALSE, 0);

    gtk_table_attach(GTK_TABLE(boxArray), subBox3[3], 10, 11, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    radio1 = gtk_radio_button_new_with_label (NULL, "Classic"); //THE FIRST RADIO BUTTON HAS NO GROUP
    radio2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio1)), "Premium");
    radio3 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio1)), "Premium Plus");

    gtk_box_pack_start(GTK_BOX(subBox3[4]), radio1, FALSE, FALSE, 0);
    g_signal_connect(radio1, "toggled", G_CALLBACK(toggledFunction), (gpointer)"0");

    gtk_box_pack_start(GTK_BOX(subBox3[4]), radio2, FALSE, FALSE, 0);
    g_signal_connect(radio2, "toggled", G_CALLBACK(toggledFunction), (gpointer)"1");
    gtk_box_pack_start(GTK_BOX(subBox3[4]), radio3, FALSE, FALSE, 0);
    g_signal_connect(radio3, "toggled", G_CALLBACK(toggledFunction), (gpointer)"2");

    validButton = gtk_button_new_with_label("I choose this subscription");
    g_signal_connect(validButton, "activate", G_CALLBACK(toggledFunction), &subValue);
    gtk_box_pack_start(GTK_BOX(subBox3[4]), validButton, FALSE, FALSE, 0);
    gtk_table_attach(GTK_TABLE(boxArray), subBox3[4], 11, 12, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);


    frame = gtk_frame_new("Our services");
    gtk_box_pack_start(GTK_BOX(vBox3), frame, FALSE, FALSE, 0);
    subvBox3b = gtk_vbox_new(FALSE, 0);

    gtk_container_add(GTK_CONTAINER(frame), subvBox3b);
    sTabLabel = g_strdup_printf("Offers and subscription");
    pTabLabel = gtk_label_new(sTabLabel);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vBox3, pTabLabel);


    /** PAGE PAYMENT **/

    GtkWidget *vBox7;
    GtkWidget *subvBox7b;
    GtkWidget *textPaymentArray[4];

    vBox7 = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vBox7);
    headerTitle = g_locale_from_utf8("\n\n<b><big>Payment</big></b>\n\n", -1, NULL, NULL, NULL);
    headerTitleLabel = gtk_label_new(headerTitle);
    gtk_label_set_use_markup(GTK_LABEL(headerTitleLabel), TRUE);
    gtk_label_set_justify(GTK_LABEL(headerTitleLabel), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(vBox7), headerTitleLabel, FALSE, FALSE, 0);
    frame = gtk_frame_new("Credit Card Information");
    gtk_box_pack_start(GTK_BOX(vBox7), frame, FALSE, FALSE, 0);
    subvBox7b = gtk_vbox_new(FALSE, 0);

    gtk_container_add(GTK_CONTAINER(frame), subvBox7b);

    formArray = gtk_table_new(5, 12, TRUE);
    gtk_box_pack_start(GTK_BOX(subvBox7b), formArray, FALSE, FALSE, 10);
    textLabel = gtk_label_new ("\nCredit Card Number (XXXX_XXXX_XXXX_XXXX)");
    textPaymentArray[0] = gtk_entry_new();

    gtk_table_attach(GTK_TABLE(formArray), textLabel, 1, 2, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(formArray), textPaymentArray[0], 2, 3, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    textLabel = gtk_label_new ("Credit Card CVC (XXX)");
    textPaymentArray[1] = gtk_entry_new();

    gtk_table_attach(GTK_TABLE(formArray), textLabel, 1, 2, 1, 2, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(formArray), textPaymentArray[1], 2, 3, 1, 2, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);


    textLabel = gtk_label_new ("Expired Date (MMYYYY)");
    textPaymentArray[2] = gtk_entry_new();

    gtk_table_attach(GTK_TABLE(formArray), textLabel, 1, 2, 2, 3, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(formArray), textPaymentArray[2], 2, 3, 2, 3, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    textLabel = gtk_label_new ("Email");

    textPaymentArray[3] = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(formArray), textLabel, 1, 2, 3, 4, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(formArray), textPaymentArray[3], 2, 3, 3, 4, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    validButton = gtk_button_new_with_label("Confirm your payment");

    gtk_table_attach(GTK_TABLE(formArray), validButton, 3, 4, 2, 3, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    g_signal_connect(validButton, "clicked", G_CALLBACK(grabPaymentData), &textPaymentArray);


    sTabLabel = g_strdup_printf("Payment");
    pTabLabel = gtk_label_new(sTabLabel);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vBox7, pTabLabel);


    /** PAGE 4 **/
    GtkWidget * vBox4;
    GtkWidget * subvBox4b;
    GtkWidget * labelText;
    vBox4 = gtk_vbox_new(FALSE, 0);
    int placesAvailable = 50;
    char *markup;

    //MAIN TITLE
    headerTitle = g_locale_from_utf8("\n\n<b><big>Consult our parking</big></b>\n\n", -1, NULL, NULL, NULL);
    headerTitleLabel = gtk_label_new(headerTitle);
    gtk_label_set_use_markup(GTK_LABEL(headerTitleLabel), TRUE);
    gtk_label_set_justify(GTK_LABEL(headerTitleLabel), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vBox4), headerTitleLabel, FALSE, FALSE, 0);

    //FRAME
    frame = gtk_frame_new("Parking Information");
    gtk_box_pack_start(GTK_BOX(vBox4), frame, FALSE, FALSE, 0);

    /** COLLECT DATA FROM DATABASE**/
    /** TOTAL PARKING SPOTS AVAILABLE**/
    subvBox4b = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(frame), subvBox4b);

    labelText = gtk_label_new ("Parking spots available: 50\nThere is x parking space left.");


    gtk_box_pack_start(GTK_BOX(subvBox4b), labelText, FALSE, FALSE, 0);


    sTabLabel = g_strdup_printf("Our parking");
    pTabLabel = gtk_label_new(sTabLabel);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vBox4, pTabLabel);

    g_free(markup);


    /** PAGE 5 **/
    GtkWidget * vBox5;
    vBox5 = gtk_vbox_new(FALSE, 0);
    GtkWidget * subvBox5b;
    subvBox5b = gtk_vbox_new(FALSE, 0);
    int value;
    //GtkWidget * labelText;


    //MAIN TITLE
    headerTitle = g_locale_from_utf8("\n\n<b><big>Consult your reservation</big></b>\n\n", -1, NULL, NULL, NULL);
    headerTitleLabel = gtk_label_new(headerTitle);
    gtk_label_set_use_markup(GTK_LABEL(headerTitleLabel), TRUE);
    gtk_label_set_justify(GTK_LABEL(headerTitleLabel), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vBox5), headerTitleLabel, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(vBox5), subvBox5b, FALSE, FALSE, 0);
    labelText = gtk_label_new ("Before checking your reservation, please enter your car numberplate");

    gtk_box_pack_start(GTK_BOX(subvBox5b), labelText, FALSE, FALSE, 0);
    formArray = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(subvBox5b), formArray, FALSE, FALSE, 10);

    validButton = gtk_button_new_with_label("I valid");
    //g_signal_connect(validButton, "clicked", G_CALLBACK(grabEntryData), formArray);
    gtk_box_pack_start(GTK_BOX(subvBox5b), validButton, FALSE, FALSE, 0);

    g_signal_connect(validButton, "clicked", G_CALLBACK(grabEntryData), formArray);


    g_free(text);

    sTabLabel = g_strdup_printf("Consult your reservation");
    pTabLabel = gtk_label_new(sTabLabel);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vBox5, pTabLabel);


    /** PAGE 6 - ADMINISTRATOR **/
    GtkWidget * vBox6;
    vBox6 = gtk_vbox_new(FALSE, 0);
    GtkWidget * subvBox6b;
    subvBox6b = gtk_vbox_new(FALSE, 0);

    hbox = gtk_hbox_new(FALSE, 0);

    GtkWidget * listArray;
    listArray = gtk_table_new(50, 20, FALSE);
     gtk_box_pack_start(GTK_BOX(subvBox6b), listArray, FALSE, FALSE, 0);

    textLabel = gtk_label_new("ID");
    gtk_table_attach(listArray, textLabel, 1, 0, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 0);

    headerTitle = g_locale_from_utf8("\n\n<b><big>Administrator</big></b>\n\n", -1, NULL, NULL, NULL);
    headerTitleLabel = gtk_label_new(headerTitle);
    gtk_label_set_use_markup(GTK_LABEL(headerTitleLabel), TRUE);
    gtk_label_set_justify(GTK_LABEL(headerTitleLabel), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vBox6), headerTitleLabel, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(vBox6), subvBox6b, FALSE, FALSE, 0);

    frame = gtk_frame_new("Our members");
    gtk_box_pack_start(GTK_BOX(subvBox6b), frame, FALSE, FALSE, 0);

    sTabLabel = g_strdup_printf("Administrator");
    pTabLabel = gtk_label_new(sTabLabel);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vBox6, pTabLabel);

    g_free(sTabLabel);
    g_free(headerTitle);

    gtk_widget_show_all(window);

    gtk_main();

    return EXIT_SUCCESS;
}
/** RESERVATION - COLLECT WHICH SUBSCRIPTION **/
int toggledFunction(GtkWidget *widget, gpointer data){

    int * sub1; //CLASSIC
    int * sub2; //PREMIUM
    int * sub3; //PREMIUM PLUS

    if(strcmp((char*)data, "0") == 0){
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))){
            sub1 = atoi(data);
            //printf("\nAbonnement %d choisi", sub1);

        }
    }
    if(strcmp((char*)data, "1") == 0){
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))){
            sub2 = atoi(data);
            //printf("\nAbonnement %d choisi", sub2);

        }
    }
    if(strcmp((char*)data, "2") == 0){
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))){
            sub3 = atoi(data);
            //printf("\nAbonnement %d choisi", sub3);

        }
    }
    if(sub1 == 0 || sub2 == 1 || sub3 == 2){
        printf("Vous avez choisi l'abonnement %d", atoi(data));
    }

}


/** REGISTRATION FORM - COLLECT DATA **/
static void grabRegistrationFormData(GtkWidget *widget, gpointer data, char *name, char *surname, char *email, char *password, char *password2){

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

       /*if(strcmp(password2,password)==0)
    {
        MYSQL *mysql;
        char request[150];
        mysql = mysql_init(NULL);
        mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "option");

        if(mysql_real_connect(mysql, "127.0.0.1", "root","", "Parking", 0, NULL, 0))
        {
            messageSuccess();
            client_sing_in(mysql,name,surname,email,password);
            mysql_close(mysql);
        }
        else {
            messageErrorConnection();
        }
    }
    else
    {
            messageErrorPassword();
    }*/


}
static void grabPaymentData(GtkWidget *widget, gpointer data){

    GtkWidget **value = data;
    char *information[4];
    information[0] = gtk_entry_get_text(GTK_ENTRY(value[0]));
    printf("Card number: %s\n", information[0]);
    information[1] = gtk_entry_get_text(GTK_ENTRY(value[1]));
    printf("Card CVC: %s\n", information[1]);
    information[2] = gtk_entry_get_text(GTK_ENTRY(value[2]));
    printf("Date expiration: %s\n", information[2]);
    information[3] = gtk_entry_get_text(GTK_ENTRY(value[3]));
    printf("Email: %s\n", information[3]);

    if(strlen(information[0]) != 16 || strlen(information[1]) != 3 || strlen(information[2]) != 6){
        messageErrorInvalidCC();
    }else{
        messageSuccessPayment();
    }

}

static void grabReservationData(GtkWidget *spinner, gpointer data, int *day, int *month, int *year, int *hour, int *minute, int *day2, int *month2, int *year2, int *hour2, int *minute2, int *fuel, int *carWashInside, int *carWashOutside, int *carWashTotal){

    GtkSpinButton **value = data;
    int * option;
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

    fuel = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(value[10]));

    option = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(value[11]));
    if(option == 1){

        carWashInside = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(value[11]));
        printf("\nInside: 1");
        //UPDATE lavage_int to 1
    }else if(option == 2){

        carWashOutside = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(value[11]));
        printf("\nOutside: 1");

        //UPDATE lavage_ext to 1
    }else if(option == 3){

        carWashTotal = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(value[11]));
        printf("\nTotal: 1");
        //UPDATE lavage_total to 1
    }

    printf("\n\nTO:\nDay: %d\nMonth: %d\nYear: %d\nAt %d:%d", day2, month2, year2, hour2, minute2);


    /** CHECK IF ERROR **/
    if(year2 >= year){
        printf("\nYear OK");
        if(month2 >= month){
            printf("\nMonth OK");
            if(day2 >= day){
                printf("\nDay OK");
                if(hour2 >= hour){
                    printf("\nHour OK");
                    if(minute2 >= minute){
                        printf("\nMinute OK\nDONE!");
                    }else{
                        messageError();
                    }
                }else{
                    messageError();
                }
            }else{
                messageError();
            }
        }else{
            messageError();
        }
    }else{
        messageError();
    }

    printf("ok");

}
/** FOR ADDING THE CAR NUMBERPLATE AND CHECK IF ALREADY EXISTS ON DATABASE **/
static void grabCarId(GtkWidget *widget, gpointer data){

    //CAR REGISTRATION
    char *carRegistration;
    carRegistration = gtk_entry_get_text(GTK_ENTRY((char*)data));
    printf("\n%s", carRegistration);

    if(strlen(carRegistration) != 7){
        messageErrorCar();

    }

}
/** FOR CHECKING IF THE CAR NUMBERPLATE EXIST ON DATABASE**/
static void grabEntryData(GtkWidget *widget, gpointer data){

    int value = 0;
    //CAR REGISTRATION
    char *carRegistration;
    carRegistration = gtk_entry_get_text(GTK_ENTRY((char*)data));
    printf("\n%s", carRegistration);


    /** IF OK **/
    if(strlen(carRegistration) == 7){
        GtkWidget *window;
        GtkWidget *vBox;
        GtkWidget *frame;
        GtkWidget *text;
        GtkWidget *textArray;

        GtkWidget *button;

        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window), "PARK'CAR");
        gtk_window_set_default_size(GTK_WINDOW(window), 1000, 720);
        g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

        vBox = gtk_vbox_new(FALSE, 0);
        gtk_container_add(GTK_CONTAINER(window), vBox);

        frame = gtk_frame_new("My reservation");
        gtk_box_pack_start(GTK_BOX(vBox), frame, FALSE, FALSE, 0);

        textArray = gtk_table_new(6, 6, FALSE);
        gtk_box_pack_start(frame, button, FALSE, FALSE, 0);
        text = gtk_label_new("Planned date");

        button = gtk_button_new_with_label("Cancel my reservation");


        gtk_table_attach(GTK_TABLE(textArray), button, 3, 4, 4, 5, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);


        gtk_widget_show_all(window);
        gtk_main();


    }else{
        messageErrorCar();

    }


}

static void messageError(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "The specified date is wrong");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}

static void messageErrorCar(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "The car number plate is invalid or doesn't exist");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}

static void messageSuccess(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Account created\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Your account has been successfully created");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageSuccessCancelled(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Account created\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Your booking successfully cancelled");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageSuccessPayment(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Payment accepted\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Your payment has been successfully accepted");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}

static void messageErrorPassword(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Warning\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Your password is incorrect");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageErrorConnection(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Warning\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Connection failed");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageErrorInvalidCC(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "The specified card number is invalid");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageSubscriptionChosen(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Thank you!\n");
  gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG (dialog), "You chose the ");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}

