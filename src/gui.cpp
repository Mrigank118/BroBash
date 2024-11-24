#include "gui.h"
#include "linkedlist.h"  
#include "commands.h"
#include <gtk/gtk.h>
#include "datastructure.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include <limits.h>

using namespace std;

extern LinkedList commandHistory;
extern DirectoryTree directoryTree;
GtkWidget *text_view; 
GtkTextBuffer *text_buffer;
GtkTextTagTable *tag_table; 
GtkTextTag *prompt_tag, *input_tag, *output_tag;

string getPrompt() {
    return directoryTree.getCurrentPath() + " > ";
}

void initialize_text_tags() {
    tag_table = gtk_text_buffer_get_tag_table(text_buffer);

    prompt_tag = gtk_text_tag_new("prompt_tag");
    g_object_set(prompt_tag, "foreground", "green", "weight", PANGO_WEIGHT_BOLD, NULL);
    gtk_text_tag_table_add(tag_table, prompt_tag);

    input_tag = gtk_text_tag_new("input_tag");
    g_object_set(input_tag, "foreground", "cyan", NULL); 
    gtk_text_tag_table_add(tag_table, input_tag);

    output_tag = gtk_text_tag_new("output_tag");
    g_object_set(output_tag, "foreground", "white", NULL);
    gtk_text_tag_table_add(tag_table, output_tag);
}

void append_output(const char* text, GtkTextTag* tag) {
    GtkTextIter iter;
    gtk_text_buffer_get_end_iter(text_buffer, &iter);

    gtk_text_buffer_insert_with_tags(text_buffer, &iter, text, -1, tag, NULL);
    gtk_text_buffer_insert(text_buffer, &iter, "\n", -1);

    gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(text_view), &iter, 0.0, TRUE, 0.0, 0.0);
}

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    if (event->keyval == GDK_KEY_Return) {
        GtkTextIter start, end;
        GtkTextBuffer *text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));

        gtk_text_buffer_get_end_iter(text_buffer, &end);
        gtk_text_buffer_get_iter_at_line_offset(text_buffer, &start, gtk_text_iter_get_line(&end), 0);

        gchar *input_text = gtk_text_buffer_get_text(text_buffer, &start, &end, FALSE);
        string command(input_text);

        size_t prompt_pos = command.find(" > ");
        if (prompt_pos != string::npos) {
            command = command.substr(prompt_pos + 3);
        }

        command = trim(command);

        if (command.empty()) {
            return TRUE;
        }

        gtk_text_buffer_delete(text_buffer, &start, &end);
        append_output(command.c_str(), input_tag);

        string output = parseBhaiLang(command);

        if (!output.empty()) {
            append_output(("\n" + output).c_str(), output_tag);
        }

        append_output(getPrompt().c_str(), prompt_tag);

        g_free(input_text);

        return TRUE;
    }

    if (event->keyval == GDK_KEY_Up || event->keyval == GDK_KEY_Down) {
        GtkTextIter start, end;
        GtkTextBuffer *text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
        gtk_text_buffer_get_end_iter(text_buffer, &end);
        gtk_text_buffer_get_iter_at_line_offset(text_buffer, &start, gtk_text_iter_get_line(&end), 0);

        string command;

        if (event->keyval == GDK_KEY_Up) {
            command = commandHistory.getPreviousCommand();
        } else if (event->keyval == GDK_KEY_Down) {
            command = commandHistory.getNextCommand();
        }

        if (!command.empty()) {
            gtk_text_buffer_delete(text_buffer, &start, &end);
            gtk_text_buffer_insert(text_buffer, &end, command.c_str(), -1);
            gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(text_view), &end, 0.0, TRUE, 0.0, 0.0);
        }

        return TRUE;
    }

    return FALSE;
}

void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *scroll_window;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "BroBash Terminal");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    scroll_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scroll_window);

    text_view = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), TRUE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), TRUE);
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(text_view), TRUE);

    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_container_add(GTK_CONTAINER(scroll_window), text_view);

    initialize_text_tags();

    append_output("Welcome to BroBash (Bhai Lang Terminal)!", output_tag);
    append_output("Type your commands below and press Enter:", output_tag);
    append_output(getPrompt().c_str(), prompt_tag);

    g_signal_connect(text_view, "key-press-event", G_CALLBACK(on_key_press), NULL);

    gtk_widget_show_all(window);
}
