#include <iostream>
#include "datastructures.h"

CommandHistory::CommandHistory() : head(nullptr) {}

CommandHistory::~CommandHistory() {
    CommandNode *current = head;
    while (current) {
        CommandNode *next = current->next;
        delete current;
        current = next;
    }
}

void CommandHistory::addCommand(const std::string &command) {
    CommandNode *newNode = new CommandNode{command, head};
    head = newNode;
}

void CommandHistory::displayHistory() const {
    CommandNode *current = head;
    while (current) {
        std::cout << current->command << std::endl;
        current = current->next;
    }
}
