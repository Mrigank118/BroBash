#include <gtk/gtk.h>
#include <iostream>
#include <cstdio>
#include <string>

// Function to execute a command and display output
void execute_command(const gchar *command, GtkTextView *text_view) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);
    GtkTextIter end_iter;
    gtk_text_buffer_get_end_iter(buffer, &end_iter);

    // Run the command and capture both stdout and stderr
    std::string full_command = std::string(command) + " 2>&1"; // Redirect stderr to stdout
    FILE *fp = popen(full_command.c_str(), "r");
    if (fp == NULL) {
        gtk_text_buffer_insert(buffer, &end_iter, "Failed to run command\n", -1);
        return;
    }

    // Read the command output and display it
    char result[1024];
    gtk_text_buffer_insert(buffer, &end_iter, "\n", -1);  // Insert newline for output
    while (fgets(result, sizeof(result), fp) != NULL) {
        gtk_text_buffer_insert(buffer, &end_iter, result, -1);
    }

    // Close the file pointer
    pclose(fp);

    // Scroll the text view to the end
    gtk_text_buffer_get_end_iter(buffer, &end_iter);
    gtk_text_view_scroll_to_iter(text_view, &end_iter, 0.0, FALSE, 0.0, 1.0);
}

// Callback function to capture key press events in the text view
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    GtkTextView *text_view = GTK_TEXT_VIEW(widget);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);
    GtkTextIter end_iter;

    if (event->keyval == GDK_KEY_Return) { // If Enter is pressed
        gtk_text_buffer_get_end_iter(buffer, &end_iter);
        gchar *text;

        // Get the current command by extracting text after the last prompt
        GtkTextIter start_iter;
        gtk_text_buffer_get_iter_at_offset(buffer, &start_iter, gtk_text_iter_get_offset(&end_iter) - 1);
        text = gtk_text_buffer_get_text(buffer, &start_iter, &end_iter, FALSE);

        // Extract the last command from the text and execute it
        if (text != NULL && *text != '\0') {
            execute_command(text, text_view);
        }

        g_free(text);

        // Insert a new prompt on a new line
        gtk_text_buffer_get_end_iter(buffer, &end_iter);
        gtk_text_buffer_insert(buffer, &end_iter, "\n", -1);  // Insert newline
        gtk_text_buffer_insert_with_tags_by_name(buffer, &end_iter, "BroBash:~$ ", -1, "green_prompt");

        // Prevent the default behavior of Enter key (newline creation)
        return TRUE;
    }

    return FALSE;  // Continue with normal event handling for other keys
}

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "BroBash Terminal");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a text view to display the output and allow input
    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), TRUE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), TRUE);

    // Apply black background and white text styling
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "textview { background-color: black; color: white; }", -1, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(text_view);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Create a text tag table and a green prompt tag
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextTagTable *tag_table = gtk_text_buffer_get_tag_table(buffer);
    GtkTextTag *green_prompt = gtk_text_tag_new("green_prompt");
    g_object_set(green_prompt, "foreground", "green", "editable", FALSE, NULL); // Green color, non-editable
    gtk_text_tag_table_add(tag_table, green_prompt);

    // Create a scrolled window for the text view
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    // Set an initial prompt with green text
    GtkTextIter iter;
    gtk_text_buffer_get_end_iter(buffer, &iter);
    gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, "BroBash:~$ ", -1, "green_prompt");

    // Connect key press event for the text view to detect Enter key
    g_signal_connect(text_view, "key-press-event", G_CALLBACK(on_key_press), NULL);

    // Show all widgets in the window
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
