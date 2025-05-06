// commands.h

#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include "hashtable.h"  
using namespace std;
extern HashTable metadataTable;  
 string banaoCommand(const  string& fileName);
 string dikhaoCommand();
 string mitaoCommand(const  string& fileName);

 string parseBhaiLang(const  string& input);
 string trim(const  string& str);  
 string getPrompt();

#endif
