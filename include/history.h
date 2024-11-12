#ifndef HISTORY_H
#define HISTORY_H

#include <string>
#include <vector>

// Class to manage the history of commands
class History {
public:
    // Add a command to the history
    void addCommand(const std::string& command);

    // Get the entire history as a string
    std::string getHistory() const;

    // Clear the history
    void clearHistory();

private:
    std::vector<std::string> historyList;
};

#endif // HISTORY_H
