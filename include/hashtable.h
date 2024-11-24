#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <list>
#include <utility>

using namespace std;

class HashTable {
public:
   
    struct Metadata {
        string filePath;
        size_t fileSize;
        string lastModified;
    };

    HashTable(size_t size = 100);
    ~HashTable();

    
    void incrementCommandCount(const string& command);
    int getCommandCount(const string& command);

    void insertFileMetadata(const string& key, const Metadata& metadata);
    Metadata* getFileMetadata(const string& key);
    void removeFileMetadata(const string& key);

    
    vector<pair<int, int>> searchPattern(const string& fileName, const string& pattern);
    vector<pair<int, int>>* getPatternOccurrences(const string& fileName, const string& pattern);

private:
    vector<list<pair<string, int>>> commandTable;  
    vector<list<pair<string, Metadata>>> metadataTable;  
    vector<list<pair<string, vector<pair<int, int>>>>> patternOccurrences;  
    size_t tableSize;

    
    size_t hashFunction(const string& key) const;
};

#endif // HASHTABLE_H
