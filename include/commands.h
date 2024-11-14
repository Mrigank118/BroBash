// commands.h

#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

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
