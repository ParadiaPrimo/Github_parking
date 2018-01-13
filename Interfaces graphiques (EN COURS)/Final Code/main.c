#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include <winsock2.h>
#include "clientParking.h"


static void messageError();
static void grabCarId(GtkWidget *widget, gpointer data);
static void grabRegistrationFormData(GtkWidget *widget, gpointer data, char *name, char *surname, char *email, char *password, char *password2);
static void grabReservationData(GtkWidget *spinner, gpointer data, int *day, int *month, int *year, int *hour, int *minute, int *day2, int *month2, int *year2, int *hour2, int *minute2);
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
    GtkWidget *subText;
    GtkWidget *textLabel;
    gchar *text;

    GtkWidget *frame;
    GtkWidget *vBoxFrame;

    GtkWidget *box, *combo;
    GtkWidget *spinner[9];
    GtkAdjustment *adj;

    vBox2 = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vBox);
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


    formArray = gtk_table_new(5, 2, TRUE);
    gtk_box_pack_start(GTK_BOX(vBox2), formArray, FALSE, FALSE, 10);
    //LICENSE PLATE
    arrayText = gtk_label_new("Enter your car registration");
    subText = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(formArray), arrayText, 0, 1, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);
    gtk_table_attach(GTK_TABLE(formArray), subText, 1, 2, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    validButton = gtk_button_new_with_label("Book my parking space");
    gtk_table_attach(GTK_TABLE(formArray), validButton, 1, 2, 1, 2, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 10);

    g_signal_connect(validButton, "clicked", G_CALLBACK(grabReservationData), &spinner);
    printf("\npremiere fonction");
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

    /** PAGE 4 **/
    GtkWidget * vBox4;
    vBox4 = gtk_vbox_new(FALSE, 0);

    headerTitle = g_locale_from_utf8("\n\n<b><big>Consult our parking</big></b>\n\n", -1, NULL, NULL, NULL);
    headerTitleLabel = gtk_label_new(headerTitle);
    gtk_label_set_use_markup(GTK_LABEL(headerTitleLabel), TRUE);
    gtk_label_set_justify(GTK_LABEL(headerTitleLabel), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vBox4), headerTitleLabel, FALSE, FALSE, 0);

    frame = gtk_frame_new("Car Place");
    gtk_box_pack_start(GTK_BOX(vBox4), frame, FALSE, FALSE, 0);
    sTabLabel = g_strdup_printf("Our parking");
    pTabLabel = gtk_label_new(sTabLabel);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vBox4, pTabLabel);

    /** PAGE 5 **/
    GtkWidget * vBox5;
    vBox5 = gtk_vbox_new(FALSE, 0);

    headerTitle = g_locale_from_utf8("\n\n<b><big>Consult your reservation</big></b>\n\n", -1, NULL, NULL, NULL);
    headerTitleLabel = gtk_label_new(headerTitle);
    gtk_label_set_use_markup(GTK_LABEL(headerTitleLabel), TRUE);
    gtk_label_set_justify(GTK_LABEL(headerTitleLabel), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vBox5), headerTitleLabel, FALSE, FALSE, 0);

    sTabLabel = g_strdup_printf("Consult your reservation");
    pTabLabel = gtk_label_new(sTabLabel);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vBox5, pTabLabel);


    /** PAGE 6 - ADMINISTRATOR **/
    GtkWidget * vBox6;
    vBox6 = gtk_vbox_new(FALSE, 0);

    headerTitle = g_locale_from_utf8("\n\n<b><big>Administrator</big></b>\n\n", -1, NULL, NULL, NULL);
    headerTitleLabel = gtk_label_new(headerTitle);
    gtk_label_set_use_markup(GTK_LABEL(headerTitleLabel), TRUE);
    gtk_label_set_justify(GTK_LABEL(headerTitleLabel), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vBox6), headerTitleLabel, FALSE, FALSE, 0);

    sTabLabel = g_strdup_printf("Administrator");
    pTabLabel = gtk_label_new(sTabLabel);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vBox6, pTabLabel);

    subvBox3b = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(frame), subvBox3b);

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

       if(strcmp(password2,password)==0)
    {
        MYSQL *mysql;
        char request[150];
        mysql = mysql_init(NULL);
        mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "option");

        if(mysql_real_connect(mysql, "127.0.0.1", "root","", "Parking", 0, NULL, 0))
        {
            printf("Connexion OK! \n");
            client_sing_in(mysql,name,surname,email,password);
            mysql_close(mysql);
        }
        else {
            printf("Erreur connexion!");
        }
    }
    else
    {
            printf("ERROR : The password is not correct");
    }


}

static void grabReservationData(GtkWidget *spinner, gpointer data, int *day, int *month, int *year, int *hour, int *minute, int *day2, int *month2, int *year2, int *hour2, int *minute2){

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

    /** CHECK IF ERROR **/
    /*if(year2 >= year){
        printf("\nYear OK");
        if(month2 >= month){
            printf("\nMonth OK");
            if(day2 >= day){
                printf("\nDay OK");
                if(hour2 >= hour){
                    printf("\nHour OK");
                    if(minute2 >= minute){
                        printf("\nMinute OK\nDONE!");
                    }
                }
            }
        }
    }else{
        //g_signal_connect(G_OBJECT(data), "activate", G_CALLBACK(messageError), NULL);
        messageError();
    }*/
    //ok
}
static void grabCarId(GtkWidget *widget, gpointer data){
    printf("Oui");
    //CAR REGISTRATION
    char *carRegistration;
    carRegistration = gtk_entry_get_text(GTK_ENTRY((char*)data));
    printf("\n%s", carRegistration);

}
static void messageError(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Warning\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "You must choose a valid date");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
