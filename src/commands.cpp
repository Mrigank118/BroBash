#include "commands.h"
#include "linkedlist.h"
#include <sys/stat.h>
#include <unistd.h>  // For chdir()
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "hashtable.h"
#include <cstdlib>
#include <stack>
#include "datastructure.h"
#include <algorithm>

using namespace std;

HashTable metadataTable;  
LinkedList commandHistory;
DirectoryTree directoryTree;  // Use the global directory tree instance

// Trim function to remove leading and trailing spaces
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return ""; // No content
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

// Function to create a file and store metadata (banao)
string banaoCommand(const string& fileName) {
    ofstream file(fileName);
    if (file) {
        struct stat fileInfo;
        if (stat(fileName.c_str(), &fileInfo) == 0) {
            // Populate metadata
            HashTable::Metadata metadata;
            metadata.filePath = fileName;
            metadata.fileSize = fileInfo.st_size;
            metadata.lastModified = ctime(&fileInfo.st_mtime);
            metadata.lastModified.erase(remove(metadata.lastModified.begin(), metadata.lastModified.end(), '\n'), metadata.lastModified.end());

            // Insert metadata into hash table
            metadataTable.insertFileMetadata(fileName, metadata);
            return "Bhai! File '" + fileName + "' ban gaya aur metadata store ho gaya!";
        }
    } else {
        return "Bhai! Error: File '" + fileName + "' nahi ban paya!";
    }
    return "Bhai! Kuch gadbad hai!";
}

// Function to list files (dikhao)
string dikhaoCommand() {
    string output = "Bhai! Files ka list dikhao...\n";

    // List files from the current directory
    for (const auto& [name, node] : directoryTree.current->children) {
        output += "- " + name + "\n";
    }

    return output;
}

// Function to delete a file and remove metadata (mitao)
string mitaoCommand(const string& fileName) {
    if (remove(fileName.c_str()) == 0) {
        metadataTable.removeFileMetadata(fileName);  // Remove metadata from hash table
        return "Bhai! File '" + fileName + "' mita diya gaya!";
    } else {
        return "Bhai! Error: File '" + fileName + "' nahi mita!";
    }
}
// Function to search for a pattern in a file (dhoondo)
string dhoondoCommand(const string& fileName, const string& pattern) {
    vector<pair<int, int>> occurrences = metadataTable.searchPattern(fileName, pattern);

    if (occurrences.empty()) {
        return "Bhai! Pattern '" + pattern + "' file '" + fileName + "' mein nahi mila.";
    }

    string output = "Bhai! Pattern '" + pattern + "' mila:\n";
    for (const auto& occurrence : occurrences) {
        output += "Line " + to_string(occurrence.first) + ", Position " + to_string(occurrence.second) + "\n";
    }

    return output;
}

// Function to get file info (jaane)
string jaaneCommand(const string& fileName) {
    // Retrieve file metadata from hash table
    HashTable::Metadata* meta = metadataTable.getFileMetadata(fileName);
    if (meta) {
        return "Bhai! Dekho file ke baare mein kuch baatein:\n"
               "File ka naam: " + meta->filePath + "\n"
               "Size: " + to_string(meta->fileSize) + " bytes\n"
               "Last Modified: " + meta->lastModified;
    }
    return "Bhai! Kuch gadbad hai, metadata fetch karne mein!";
}

// Parse BhaiLang command and return output
string parseBhaiLang(const string& input) {
    string output;
    size_t spacePos = input.find(" ");
    string command = input.substr(0, spacePos);
    string arg = (spacePos != string::npos) ? input.substr(spacePos + 1) : "";

    // Add the command to history
    commandHistory.addCommand(input);

    // Increment the command count
    metadataTable.incrementCommandCount(command);  // Ensure this line is called

    // Check for different commands and call respective functions
    if (command == "banao") {
        output = banaoCommand(arg);  
    } else if (command == "dikhao") {
        output = directoryTree.dikhao();  // Tree-based directory listing
    } else if (command == "mitao") {
        output = mitaoCommand(arg);  
    } else if (command == "jaane") {
        output = jaaneCommand(arg);  
    } else if (command == "chalo") {
        output = directoryTree.chalo(arg);  // Tree-based change directory
    } else if (command == "wapas") {
        output = directoryTree.wapas();  // Go up one level
    } else if (command == "itihas") {
        output = commandHistory.itihas();  // Show all commands used
    } else if (command == "dhoondo") {
        // Split the argument into file name and search pattern
        size_t separator = arg.find(" ");
        if (separator != string::npos) {
            string fileName = arg.substr(0, separator);
            string pattern = arg.substr(separator + 1);
            output = dhoondoCommand(fileName, pattern);  // Search for a pattern
        } else {
            output = "Bhai! File aur pattern dono specify karo.";
        }
    } else if (command == "khojo") {
        output = directoryTree.khojo(arg);  // Tree-based search
    } else if (command == "banaoDir") {
        output = directoryTree.banaoDir(arg);  // Tree-based directory creation
    } else if (command == "jaha") {
        output = directoryTree.jaha();  // Show current path
    } else {
        output = "Bhai! Yeh command nahi samjha: " + command;
    }

    return output;
}
