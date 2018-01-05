#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void fill_combo_entry_month(GtkWidget *combo);
void gtk_box_pack_start(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
void gtk_box_pack_end(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
void gtk_entry_set_visibility(GtkEntry *entry, gboolean visible);
void buttonClicked(GtkWidget *widget, gpointer data);
//COLLECT SPIN'S VALUE
static void grabAll(GtkWidget *spinner, gpointer data, int *day, int *month, int *year, int *hour, int *minute, int *day2, int *month2, int *year2, int *hour2, int *minute2);
int main(int argc, char *argv[]) {

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

  return 0;
}
/*static void fill_combo_entry_month(GtkWidget *combo){

    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (combo), "always", "January");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (combo), "always", "February");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (combo), "always", "March");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (combo), "always", "April");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (combo), "always", "May");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (combo), "always", "June");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (combo), "always", "July");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (combo), "always", "August");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (combo), "always", "September");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (combo), "always", "October");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (combo), "always", "November");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (combo), "always", "December");

}*/
void buttonClicked(GtkWidget *widget, gpointer data){

    //CAR REGISTRATION
    char *carRegistration;
    carRegistration = gtk_entry_get_text(GTK_ENTRY(data));
    printf("\n%s", carRegistration);

}
static void grabAll(GtkWidget *spinner, gpointer data, int *day, int *month, int *year, int *hour, int *minute, int *day2, int *month2, int *year2, int *hour2, int *minute2){

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
