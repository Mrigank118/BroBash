#include "hashtable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <sys/stat.h>

using namespace std;

HashTable::HashTable(size_t size) : tableSize(size) {
    commandTable.resize(size);
    metadataTable.resize(size);
    patternOccurrences.resize(size);  // Resize the hash table for pattern occurrences
}

HashTable::~HashTable() {}

size_t HashTable::hashFunction(const string& key) const {
    size_t hash = 0;
    for (char c : key) {
        hash = (hash * 31) + c;
    }
    return hash % tableSize;
}

void HashTable::incrementCommandCount(const string& command) {
    size_t index = hashFunction(command);
    for (auto& pair : commandTable[index]) {
        if (pair.first == command) {
            pair.second++;
            return;
        }
    }
    commandTable[index].emplace_back(command, 1);  // If command is new, start at count 1
}

// Get command count
int HashTable::getCommandCount(const string& command) {
    size_t index = hashFunction(command);
    for (const auto& pair : commandTable[index]) {
        if (pair.first == command) {
            return pair.second;
        }
    }
    return 0;
}

// Insert file metadata
void HashTable::insertFileMetadata(const string& key, const Metadata& metadata) {
    size_t index = hashFunction(key);
    for (auto& pair : metadataTable[index]) {
        if (pair.first == key) {
            pair.second = metadata;
            return;
        }
    }
    metadataTable[index].emplace_back(key, metadata);
}

// Retrieve file metadata
HashTable::Metadata* HashTable::getFileMetadata(const string& key) {
    size_t index = hashFunction(key);
    for (auto& pair : metadataTable[index]) {
        if (pair.first == key) {
            return &pair.second;
        }
    }
    return nullptr;
}

// Remove file metadata
void HashTable::removeFileMetadata(const string& key) {
    size_t index = hashFunction(key);
    auto& bucket = metadataTable[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            return;
        }
    }
}

// Search for a pattern in a file
vector<pair<int, int>> HashTable::searchPattern(const string& fileName, const string& pattern) {
    vector<pair<int, int>> occurrences;  // To store line numbers and positions

    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Bhai! File '" << fileName << "' nahi khul rahi!" << endl;
        return occurrences;
    }

    string line;
    int lineNumber = 0;
     while (getline(file, line)) {
         lineNumber++;
        size_t pos = line.find(pattern);
        while (pos != string::npos) {
            occurrences.emplace_back(lineNumber, pos);  // Store line and position
            pos = line.find(pattern, pos + 1);         // Search for next occurrence
        }
    }

    file.close();

    // Store occurrences in the hash table
    size_t index = hashFunction ( fileName + pattern);
      patternOccurrences[index].emplace_back(fileName + pattern, occurrences);

      return occurrences;
}

// Retrieve stored pattern occurrences
vector<pair<int, int>>* HashTable::getPatternOccurrences(const string& fileName, const string& pattern) {
    size_t index = hashFunction(fileName + pattern);
    for (auto& pair : patternOccurrences[index]) {
        if (pair.first == fileName + pattern) {
            return &pair.second;
        }
    }
    return nullptr;
}
