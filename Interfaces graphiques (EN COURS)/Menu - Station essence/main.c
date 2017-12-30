#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TYPE_MASK_ENTRY             (mask_entry_get_type ())
#define MASK_ENTRY(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_MASK_ENTRY, MaskEntry))
#define MASK_ENTRY_CLASS(vtable)    (G_TYPE_CHECK_CLASS_CAST ((vtable), TYPE_MASK_ENTRY, MaskEntryClass))
#define IS_MASK_ENTRY(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_MASK_ENTRY))
#define IS_MASK_ENTRY_CLASS(vtable) (G_TYPE_CHECK_CLASS_TYPE ((vtable), TYPE_MASK_ENTRY))
#define MASK_ENTRY_GET_CLASS(inst)  (G_TYPE_INSTANCE_GET_CLASS ((inst), TYPE_MASK_ENTRY, MaskEntryClass))


typedef struct _MaskEntry MaskEntry;
struct _MaskEntry
{
  GtkEntry entry;
  gchar *mask;
};

typedef struct _MaskEntryClass MaskEntryClass;
struct _MaskEntryClass
{
  GtkEntryClass parent_class;
};


static void mask_entry_editable_init (GtkEditableInterface *iface);

G_DEFINE_TYPE_WITH_CODE (MaskEntry, mask_entry, GTK_TYPE_ENTRY,
                         G_IMPLEMENT_INTERFACE (GTK_TYPE_EDITABLE,
                                                mask_entry_editable_init));


static void
mask_entry_set_background (MaskEntry *entry)
{
  static const GdkRGBA error_color = { 1.0, 0.9, 0.9, 1.0 };

  if (entry->mask)
    {
      if (!g_regex_match_simple (entry->mask, gtk_entry_get_text (GTK_ENTRY (entry)), 0, 0))
        {
          gtk_widget_override_color (GTK_WIDGET (entry), 0, &error_color);
          return;
        }
    }

  gtk_widget_override_color (GTK_WIDGET (entry), 0, NULL);
}


static void
mask_entry_changed (GtkEditable *editable)
{
  mask_entry_set_background (MASK_ENTRY (editable));
}


static void
mask_entry_init (MaskEntry *entry)
{
  entry->mask = NULL;
}

static void
mask_entry_editable_init (GtkEditableInterface *iface)
{
  iface->changed = mask_entry_changed;
}
static void
mask_entry_class_init (MaskEntryClass *klass)
{ }
void gtk_box_pack_start(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
void gtk_box_pack_end(GtkBox* box, GtkWidget* child, gboolean expand, gboolean fill, guint padding);
static void is_capital_sensitive (GtkCellLayout   *cell_layout,
                      GtkCellRenderer *cell,
                      GtkTreeModel    *tree_model,
                      GtkTreeIter     *iter,
                      gpointer         data);
static void fill_combo_entry(GtkWidget *combo);
int main(int argc, char *argv[]) {

    GtkWidget *window;
    GtkContainer *vbox;
    GtkWidget *hbox;

    GtkWidget *toolbar;
    GtkToolItem *sep;
    GtkToolItem *exitTb;
    GtkWidget *buttonArray;
    GtkWidget *buttonLabel;
    GtkWidget *button[2];
    GtkWidget *buttonAdd;
    GtkWidget *headerTitleLabel;
    gchar *headerTitle;
    GtkWidget *textLabel;
    gchar *text;

    GtkWidget *frame;
    GtkWidget *vBoxFrame;

    GtkWidget *box, *combo, *entry;
    GtkTreeModel *model;
    GtkCellRenderer *renderer;
    GtkTreePath *path;
    GtkTreeIter iter;

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

    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, TRUE, 5);
    g_signal_connect(G_OBJECT(exitTb), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    buttonArray = gtk_table_new(1, 2, TRUE);
    buttonLabel = gtk_label_new(buttonArray);
    gtk_label_set_justify(GTK_LABEL(buttonLabel), GTK_JUSTIFY_CENTER);

    gtk_box_pack_start(GTK_BOX(vbox), buttonArray, FALSE, FALSE, 0);
    button[0] = gtk_button_new_with_label("         Continue as a guest          ");
    button[1] = gtk_button_new_with_label("         Continue as a member         ");


    gtk_table_attach(GTK_TABLE(buttonArray), button[0], 0, 1, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(buttonArray), button[1], 1, 2, 0, 1, !GTK_EXPAND | !GTK_FILL, !GTK_EXPAND, 0, 0);

    headerTitle = g_locale_from_utf8("\n\n\n<span size =\"25\">WELCOME TO PARK'CAR GAS STATION</span>\n\n\n<span size =\"12\">Choose which gas do you want</span>\n\n", -1, NULL, NULL, NULL);
    headerTitleLabel = gtk_label_new(headerTitle);
    g_free(headerTitle);
    gtk_label_set_use_markup(GTK_LABEL(headerTitleLabel), TRUE);
    gtk_label_set_justify(GTK_LABEL(headerTitleLabel), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), headerTitleLabel, FALSE, FALSE, 0);

    frame = gtk_frame_new("Gas prices");
    gtk_box_pack_start(GTK_BOX(vbox), frame, FALSE, FALSE, 0);

    vBoxFrame = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(frame), vBoxFrame);
    textLabel = gtk_label_new("Shell 2,09");
    gtk_box_pack_start(GTK_BOX(vBoxFrame), textLabel, FALSE, FALSE, 0);
    textLabel = gtk_label_new("Diesel 2,09");
    gtk_box_pack_start(GTK_BOX(vBoxFrame), textLabel, FALSE, FALSE, 0);

    frame = gtk_frame_new("Choose your gas");
    gtk_box_pack_start(GTK_BOX(vbox), frame, FALSE, FALSE, 0);

    vBoxFrame = gtk_vbox_new(TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vBoxFrame), frame, FALSE, FALSE, 0);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_set_border_width(GTK_CONTAINER(box), 30);
    gtk_container_add(GTK_CONTAINER(frame), box);

    combo = gtk_combo_box_text_new_with_entry();
    fill_combo_entry(combo);
    gtk_container_add(GTK_CONTAINER(box), combo);

    entry = g_object_new(TYPE_MASK_ENTRY, NULL);
    MASK_ENTRY (entry)->mask = "^(Shell|Diesel)$";

    gtk_container_remove(GTK_CONTAINER(combo), gtk_bin_get_child (GTK_BIN(combo)));
    gtk_container_add(GTK_CONTAINER(combo), entry);

    /*buttonAdd = gtk_button_new_with_label("Keep the button pressed");
    gtk_box_pack_start(GTK_BOX(vbox), buttonAdd, FALSE, FALSE, 0);*/
    //DISPLAY THE WINDOW
    gtk_widget_show_all(window);

    gtk_main();

  return 0;
}
static void fill_combo_entry (GtkWidget *combo){
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Shell");
  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Diesel");

}
static void is_capital_sensitive (GtkCellLayout   *cell_layout,
                      GtkCellRenderer *cell,
                      GtkTreeModel    *tree_model,
                      GtkTreeIter     *iter,
                      gpointer         data)
{
  gboolean sensitive;

  sensitive = !gtk_tree_model_iter_has_child (tree_model, iter);

  g_object_set (cell, "sensitive", sensitive, NULL);
}

