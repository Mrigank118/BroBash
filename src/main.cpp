#include <gtk/gtk.h>
#include <iostream>

// Function to execute a command
void execute_command(const gchar *command, GtkTextView *text_view) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);
    GtkTextIter end_iter;
    gtk_text_buffer_get_end_iter(buffer, &end_iter);

    // Append the entered command to the text view
    std::string command_display = "Command: " + std::string(command) + "\n";
    gtk_text_buffer_insert(buffer, &end_iter, command_display.c_str(), -1);

    // Execute the command and read the output
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        gtk_text_buffer_insert(buffer, &end_iter, "Failed to run command\n", -1);
        return;
    }

    // Read and display the output
    char result[1024];
    while (fgets(result, sizeof(result) - 1, fp) != NULL) {
        gtk_text_buffer_insert(buffer, &end_iter, result, -1);
    }

    // Close the file pointer
    pclose(fp);

    // Move the cursor to the end of the buffer and scroll the text view
    gtk_text_buffer_get_end_iter(buffer, &end_iter);
    gtk_text_view_scroll_to_iter(text_view, &end_iter, 0.0, FALSE, 0.0, 1.0);
}

// Callback function for the "Send" button
void on_send_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *entry = GTK_WIDGET(data);
    const gchar *command = gtk_entry_get_text(GTK_ENTRY(entry));

    // Get the text view to display input and output
    GtkWidget *text_view = GTK_WIDGET(g_object_get_data(G_OBJECT(widget), "text_view"));

    // Execute the command and display both input and output
    execute_command(command, GTK_TEXT_VIEW(text_view));

    // Clear the entry after sending the command
    gtk_entry_set_text(GTK_ENTRY(entry), "");
}

// Main function to initialize the GTK application
int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "BroBash Terminal");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box to hold the components
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create a text view to display the output
    GtkWidget *text_view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 0);

    // Create a text entry for user commands
    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    // Create a "Send" button
    GtkWidget *send_button = gtk_button_new_with_label("Send");
    gtk_box_pack_start(GTK_BOX(vbox), send_button, FALSE, FALSE, 0);

    // Store the text view as data for the button
    g_object_set_data(G_OBJECT(send_button), "text_view", text_view);

    // Connect the button click event to the callback function
    g_signal_connect(send_button, "clicked", G_CALLBACK(on_send_button_clicked), entry);

    // Show all widgets in the window
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
