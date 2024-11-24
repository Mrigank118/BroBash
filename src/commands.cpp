#include "commands.h"
#include "linkedlist.h"
#include <sys/stat.h>
#include <unistd.h>
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
DirectoryTree directoryTree;

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

string banaoCommand(const string& fileName) {
    ofstream file(fileName);
    if (file) {
        struct stat fileInfo;
        if (stat(fileName.c_str(), &fileInfo) == 0) {
            HashTable::Metadata metadata;
            metadata.filePath = fileName;
            metadata.fileSize = fileInfo.st_size;
            metadata.lastModified = ctime(&fileInfo.st_mtime);
            metadata.lastModified.erase(remove(metadata.lastModified.begin(), metadata.lastModified.end(), '\n'), metadata.lastModified.end());
            metadataTable.insertFileMetadata(fileName, metadata);
            return "Bhai! File '" + fileName + "' ban gaya aur metadata store ho gaya!";
        }
    } else {
        return "Bhai! Error: File '" + fileName + "' nahi ban paya!";
    }
    return "Bhai! Kuch gadbad hai!";
}

string dikhaoCommand() {
    string output = "Bhai! Files ka list dikhao...\n";
    for (const auto& [name, node] : directoryTree.current->children) {
        output += "- " + name + "\n";
    }
    return output;
}

string mitaoCommand(const string& fileName) {
    if (remove(fileName.c_str()) == 0) {
        metadataTable.removeFileMetadata(fileName);
        return "Bhai! File '" + fileName + "' mita diya gaya!";
    } else {
        return "Bhai! Error: File '" + fileName + "' nahi mita!";
    }
}

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

string jaaneCommand(const string& fileName) {
    HashTable::Metadata* meta = metadataTable.getFileMetadata(fileName);
    if (meta) {
        return "Bhai! Dekho file ke baare mein kuch baatein:\n"
               "File ka naam: " + meta->filePath + "\n"
               "Size: " + to_string(meta->fileSize) + " bytes\n"
               "Last Modified: " + meta->lastModified;
    }
    return "Bhai! Kuch gadbad hai, metadata fetch karne mein!";
}

string padhCommand(const string& fileName) {
    ifstream file(fileName);
    if (file) {
        stringstream buffer;
        buffer << file.rdbuf();
        return "Bhai! File '" + fileName + "' ka content:\n" + buffer.str();
    } else {
        return "Bhai! File '" + fileName + "' nahi mil raha!";
    }
}

string likhCommand(const string& fileName, const string& content) {
    ofstream file(fileName);
    if (file) {
        file << content;
        return "Bhai! File '" + fileName + "' mein likh diya gaya!";
    } else {
        return "Bhai! File '" + fileName + "' nahi bana sakte!";
    }
}

string parseBhaiLang(const string& input) {
    string output;
    size_t spacePos = input.find(" ");
    string command = input.substr(0, spacePos);
    string arg = (spacePos != string::npos) ? input.substr(spacePos + 1) : "";

    commandHistory.addCommand(input);
    metadataTable.incrementCommandCount(command);

    if (command == "banao") {
        output = banaoCommand(arg);
    } else if (command == "dikhao") {
        output = directoryTree.dikhao();
    } else if (command == "mitao") {
        output = mitaoCommand(arg);
    } else if (command == "jaane") {
        output = jaaneCommand(arg);
    } else if (command == "padh") {
        output = padhCommand(arg);
    } else if (command == "likh") {
        size_t contentPos = arg.find(" ");
        if (contentPos != string::npos) {
            string fileName = arg.substr(0, contentPos);
            string content = arg.substr(contentPos + 1);
            output = likhCommand(fileName, content);
        } else {
            output = "Bhai! File aur likhne ka content specify karo.";
        }
    } else if (command == "chalo") {
        output = directoryTree.chalo(arg);
    } else if (command == "wapas") {
        output = directoryTree.wapas();
    } else if (command == "itihas") {
        output = commandHistory.itihas();
    } else if (command == "dhoondo") {
        size_t separator = arg.find(" ");
        if (separator != string::npos) {
            string fileName = arg.substr(0, separator);
            string pattern = arg.substr(separator + 1);
            output = dhoondoCommand(fileName, pattern);
        } else {
            output = "Bhai! File aur pattern dono specify karo.";
        }
    } else if (command == "khojo") {
        output = directoryTree.khojo(arg);
    } else if (command == "banaoDir") {
        output = directoryTree.banaoDir(arg);
    } else if (command == "jaha") {
        output = directoryTree.jaha();
    } else if (command == "bye") {
        exit(0); // Exit the program
    } else {
        output = "Bhai! Yeh command nahi samjha: " + command;
    }

    return output;
}
