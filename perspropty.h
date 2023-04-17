#ifndef PERSPROPTY_H
#define PERSPROPTY_H
#include <gtk/gtk.h>
void all_destroy(GtkWidget *widget, gpointer user_data);
void set_row_prop(GtkWidget* new_row);
void set_textview_prop(GtkWidget* text_view);
void add_row(GtkWidget *widget, gpointer   user_data);
struct AddRowTextView{
	char* messages;
	GObject* listbox;
	GObject* scrolled_window ;
};
#endif //PERSPROPTY_H