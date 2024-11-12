#include "commands.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

// Define trim function once
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return ""; // No content
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

// Function to create a file (banao)
std::string banaoCommand(const std::string& fileName) {
    std::ofstream file(fileName);
    if (file) {
        return "File '" + fileName + "' ban gaya!\n";  // Return output as string
    } else {
        return "Error: File '" + fileName + "' nahi ban paya.\n";  // Return error as string
    }
}

// Function to list files (dikhao)
std::string dikhaoCommand() {
    std::string output = "Files ka list dikhao...\n";
    FILE* fp = popen("ls", "r");  // Executes the 'ls' command and captures the output
    if (fp != nullptr) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), fp)) {
            output += buffer;  // Append the output of 'ls' to the string
        }
        fclose(fp);
    }
    return output;  // Return the output
}

// Function to delete a file (mitao)
std::string mitaoCommand(const std::string& fileName) {
    if (remove(fileName.c_str()) == 0) {
        return "File '" + fileName + "' mita diya gaya.\n";  // Return success message as string
    } else {
        return "Error: File '" + fileName + "' nahi mita.\n";  // Return error message as string
    }
}

std::string parseBhaiLang(const std::string& input) {
    std::string output;

    // Parse the input and generate the corresponding output
    size_t spacePos = input.find(" ");
    std::string command = input.substr(0, spacePos);
    std::string arg = (spacePos != std::string::npos) ? input.substr(spacePos + 1) : "";

    if (command == "banao") {
        output = banaoCommand(arg);  // Call the function and get the result
    } else if (command == "dikhao") {
        output = dikhaoCommand();  // Call the function and get the result
    } else if (command == "mitao") {
        output = mitaoCommand(arg);  // Call the function and get the result
    } else {
        output = "Bhai, yeh command nahi samjha: " + command;  // Error message for unrecognized command
    }

    return output;
}