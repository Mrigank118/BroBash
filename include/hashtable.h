#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <list>
#include <utility>

using namespace std;

class HashTable {
public:
    // Structure to hold metadata
    struct Metadata {
        string filePath;
        size_t fileSize;
        string lastModified;
    };

    HashTable(size_t size = 100);
    ~HashTable();

    // Methods for command frequency
    void incrementCommandCount(const string& command);
    int getCommandCount(const string& command);

    // Methods for file metadata
    void insertFileMetadata(const string& key, const Metadata& metadata);
    Metadata* getFileMetadata(const string& key);
    void removeFileMetadata(const string& key);

    // Methods for pattern searching
    vector<pair<int, int>> searchPattern(const string& fileName, const string& pattern);
    vector<pair<int, int>>* getPatternOccurrences(const string& fileName, const string& pattern);

private:
    vector<list<pair<string, int>>> commandTable;  // Command frequency table
    vector<list<pair<string, Metadata>>> metadataTable;  // File metadata table
    vector<list<pair<string, vector<pair<int, int>>>>> patternOccurrences;  // Pattern occurrence table
    size_t tableSize;

    // Hash functions
    size_t hashFunction(const string& key) const;
};

#endif // HASHTABLE_H
