#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <unordered_map>

class CommandLookup {
private:
    std::unordered_map<std::string, std::string> commandTable;

public:
    CommandLookup();
    void addCommand(const std::string& cmd, const std::string& desc);
    std::string getCommandInfo(const std::string& cmd);
};

#endif
