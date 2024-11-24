// commands.h

#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
// In commands.h
#include "hashtable.h"  // Include the header where HashTable is defined

extern HashTable metadataTable;  // Declaration of the global metadataTable

 // Declaration, not definition


// Declare Bhai Lang command functions
std::string banaoCommand(const std::string& fileName);
std::string dikhaoCommand();
std::string mitaoCommand(const std::string& fileName);

// Command parser
std::string parseBhaiLang(const std::string& input);
std::string trim(const std::string& str);  // Declare trim function here

// Declarations for other commands
std::string getPrompt();
std::string puraniKahaniCommand();  
std::string aakhriCommand();

#endif
