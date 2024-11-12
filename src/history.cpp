#include "history.h"
#include <iostream>

void History::addCommand(const std::string& command) {
    // Add the command to the history
    historyList.push_back(command);
}

std::string History::getHistory() const {
    // Return the history as a formatted string
    std::string result = "Command History:\n";
    for (const auto& command : historyList) {
        result += command + "\n";
    }
    return result.empty() ? "No history available.\n" : result;
}

void History::clearHistory() {
    // Clear the history list
    historyList.clear();
}
