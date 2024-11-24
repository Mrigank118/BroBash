// commands.h

#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include "hashtable.h"  

extern HashTable metadataTable;  
std::string banaoCommand(const std::string& fileName);
std::string dikhaoCommand();
std::string mitaoCommand(const std::string& fileName);

std::string parseBhaiLang(const std::string& input);
std::string trim(const std::string& str);  
std::string getPrompt();

#endif
