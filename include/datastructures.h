#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <string>

struct CommandNode {
    std::string command;
    CommandNode *next;
};

class CommandHistory {
public:
    CommandHistory();
    ~CommandHistory();
    void addCommand(const std::string& command);
    void displayHistory() const;

private:
    CommandNode *head;
};

#endif
