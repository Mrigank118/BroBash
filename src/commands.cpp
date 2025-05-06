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

int levenshteinDistance(const string &s1, const string &s2) {
    int len1 = s1.size(), len2 = s2.size();
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

    for (int i = 0; i <= len1; i++) dp[i][0] = i;
    for (int j = 0; j <= len2; j++) dp[0][j] = j;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }
    return dp[len1][len2];
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

// Boyer-Moore Preprocessing for Bad Character Heuristic
vector<int> preprocessBadChar(const string &pattern) {
    vector<int> badChar(256, -1);
    for (int i = 0; i < pattern.size(); i++)
        badChar[pattern[i]] = i;
    return badChar;
}

// Boyer-Moore Pattern Matching Algorithm
vector<int> boyerMooreSearch(const string &text, const string &pattern) {
    int m = pattern.size();
    int n = text.size();
    vector<int> badChar = preprocessBadChar(pattern);
    vector<int> result;

    int shift = 0;
    while (shift <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        if (j < 0) {
            result.push_back(shift);
            shift += (shift + m < n) ? m - badChar[text[shift + m]] : 1;
        } else {
            shift += max(1, j - badChar[text[shift + j]]);
        }
    }
    return result;
}

// Updated dhoondoCommand with Boyer-Moore
string dhoondoCommand(const string& fileName, const string& pattern) {
    ifstream file(fileName);
    if (!file) {
        return "Bhai! File '" + fileName + "' nahi mil rahi.";
    }

    string line;
    int lineNum = 0;
    vector<pair<int, int>> occurrences;

    while (getline(file, line)) {
        lineNum++;
        vector<int> matches = boyerMooreSearch(line, pattern);
        for (int pos : matches) {
            occurrences.push_back({lineNum, pos});
        }
    }

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

    // ✅ List of valid commands
    vector<string> validCommands = {"banao", "dikhao", "mitao", "jaane", "padh", "likh",
                                    "chalo", "wapas", "itihas", "dhoondo", "khojo",
                                    "banaoDir", "jaha", "bye"};

    // ✅ Check if command is valid
    if (find(validCommands.begin(), validCommands.end(), command) == validCommands.end()) {
        // ✅ Find closest match using Levenshtein Distance
        string closestMatch = "";
        int minDistance = INT_MAX;

        for (const string &validCommand : validCommands) {
            int distance = levenshteinDistance(command, validCommand);
            if (distance < minDistance) {
                minDistance = distance;
                closestMatch = validCommand;
            }
        }

        // ✅ Suggest the closest valid command
        return "Bhai! Yeh command nahi samjha: " + command + "\nKya tum '" + closestMatch + "' likhna chahte the?";
    }

    // ✅ If command is valid, execute normally
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
        exit(0);
    }

    return output;
}