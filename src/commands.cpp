#include "commands.h"
#include "linkedlist.h"  // Add this line to include the linked list

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;  // Add this line to use the std namespace


LinkedList commandHistory; 
// Define trim function once
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return ""; // No content
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

// Function to create a file (banao)
string banaoCommand(const string& fileName) {
    ofstream file(fileName);
    if (file) {
        return "File '" + fileName + "' ban gaya!\n";  // Return output as string
    } else {
        return "Error: File '" + fileName + "' nahi ban paya.\n";  // Return error as string
    }
}

// Function to list files (dikhao)
// Function to list files with details (dikhao)
string dikhaoCommand() {
    string output = "Files ka list dikhao...\n";
    FILE* fp = popen("ls -l", "r");  // Executes the 'ls -l' command and captures the output
    if (fp != nullptr) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), fp)) {
            output += buffer;  // Append the detailed output (including file size) of 'ls -l' to the string
        }
        fclose(fp);
    }
    return output;  // Return the detailed file list
}

// Function to delete a file (mitao)
string mitaoCommand(const string& fileName) {
    if (remove(fileName.c_str()) == 0) {
        return "File '" + fileName + "' mita diya gaya.\n";  // Return success message as string
    } else {
        return "Error: File '" + fileName + "' nahi mita.\n";  // Return error message as string
    }
}

// Parse BhaiLang command
string parseBhaiLang(const string& input) {
    string output;
    size_t spacePos = input.find(" ");
    string command = input.substr(0, spacePos);
    string arg = (spacePos != string::npos) ? input.substr(spacePos + 1) : "";

    // Add the command to history
    commandHistory.addCommand(input);

    // Check for different commands
    if (command == "banao") {
        output = banaoCommand(arg);  
    } else if (command == "dikhao") {
        output = dikhaoCommand();  
    } else if (command == "mitao") {
        output = mitaoCommand(arg);  
    } else {
        output = "Bhai, yeh command nahi samjha: " + command;
    }

    return output;
}
