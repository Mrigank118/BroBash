#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
using namespace std;
void activate(GtkApplication *app, gpointer user_data);
void append_output(const char* text); 

#endif
