#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>

void activate(GtkApplication *app, gpointer user_data);
void append_output(const char* text); // Function to update output on GUI

#endif
