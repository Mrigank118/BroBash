#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

// Declare Bhai Lang command functions
std::string banaoCommand(const std::string& fileName);
std::string  dikhaoCommand();
std::string  mitaoCommand(const std::string& fileName);
std::string trim(const std::string& str);
// Command parser
std::string parseBhaiLang(const std::string& input);

// Declare getPrompt to be used elsewhere
std::string getPrompt();
std::string mitaoCommand(const std::string& fileName);
std::string puraniKahaniCommand();  // Bhai Lang command for history
std::string aakhriCommand();  // Bhai Lang command for last command

#endif
