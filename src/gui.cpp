
#include "gui.h"
#include "linkedlist.h"  // Include the LinkedList header

#include "commands.h"
#include <gtk/gtk.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <limits.h>

extern LinkedList commandHistory;
GtkWidget *text_view; //FOR DISPLAYING TEXT
GtkTextBuffer *text_buffer;
GtkTextTagTable *tag_table; //FOR COLOUR WEIGHT ETC
GtkTextTag *prompt_tag, *input_tag, *output_tag;

// Function to get the current directory path (used as the prompt)
std::string getPrompt() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        return std::string(cwd) + " > ";
    } else {
        return "~/ > ";
    }
}

// Function to initialize text tags for colors
void initialize_text_tags() {
    tag_table = gtk_text_buffer_get_tag_table(text_buffer);

    // Define and add tags to the tag table
    prompt_tag = gtk_text_tag_new("prompt_tag");
    g_object_set(prompt_tag, "foreground", "green", "weight", PANGO_WEIGHT_BOLD, NULL);
    gtk_text_tag_table_add(tag_table, prompt_tag);

    // Brighter color for input commands
    input_tag = gtk_text_tag_new("input_tag");
    g_object_set(input_tag, "foreground", "cyan", NULL); // Changed to cyan for better visibility
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

    // Auto-scroll to the end of the text view
    gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(text_view), &iter, 0.0, TRUE, 0.0, 0.0);
}
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    if (event->keyval == GDK_KEY_Return) {
        GtkTextIter start, end;
        GtkTextBuffer *text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));

        // Get end iterator of the text buffer
        gtk_text_buffer_get_end_iter(text_buffer, &end);

        // Get the iterator at the start of the current line
        gtk_text_buffer_get_iter_at_line_offset(text_buffer, &start, gtk_text_iter_get_line(&end), 0);

        // Extract the text entered by the user (including the prompt)
        gchar *input_text = gtk_text_buffer_get_text(text_buffer, &start, &end, FALSE);
        std::string command(input_text);

        // Locate the prompt " > " and skip it
        size_t prompt_pos = command.find(" > ");
        if (prompt_pos != std::string::npos) {
            command = command.substr(prompt_pos + 3);  // Extract the user command after " > "
        }

        // Trim any leading/trailing whitespace from the command
        command = trim(command);

        if (command.empty()) {
            return TRUE;
        }

        // **Delete the current line (including the command) from the text buffer**
        gtk_text_buffer_delete(text_buffer, &start, &end);

        // **Append the command input (without the prompt)**
        append_output(command.c_str(), input_tag);

        // **Execute the Bhai Lang command** and get the output
        std::string output = parseBhaiLang(command);

        // **Append the output of the command immediately after** (in white color)
        if (!output.empty()) {
            append_output(("\n" + output).c_str(), output_tag);
        }

        // **Display a new prompt after the output** (in green color)
        append_output(getPrompt().c_str(), prompt_tag);

        // Free the allocated input text
        g_free(input_text);

        return TRUE;
    }

    // Handle up and down arrow keys for navigating history
    // Handle up and down arrow keys for navigating history
 
    // Handle up and down arrow keys for navigating history
if (event->keyval == GDK_KEY_Up || event->keyval == GDK_KEY_Down) {
    GtkTextIter start, end;
    GtkTextBuffer *text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
    gtk_text_buffer_get_end_iter(text_buffer, &end);
    gtk_text_buffer_get_iter_at_line_offset(text_buffer, &start, gtk_text_iter_get_line(&end), 0);

    std::string command;

    // Fetch the command from history
    if (event->keyval == GDK_KEY_Up) {
        command = commandHistory.getPreviousCommand();
    } else if (event->keyval == GDK_KEY_Down) {
        command = commandHistory.getNextCommand();
    }

    // If a valid command is found, update the input buffer with it
    if (!command.empty()) {
        // Clear the current line input
        gtk_text_buffer_delete(text_buffer, &start, &end);
        
        // Insert the command from history
        gtk_text_buffer_insert(text_buffer, &end, command.c_str(), -1);
        
        // Move the cursor to the end of the inserted command
        gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(text_view), &end, 0.0, TRUE, 0.0, 0.0);
    }

    return TRUE; // Event handled, no further processing required
}

    return FALSE;
}

// GTK application activation function
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