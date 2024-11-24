#include "linkedlist.h"
#include <iostream>
#include <unordered_set>
#include "commands.h"

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    current = nullptr;
}

LinkedList::~LinkedList() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
}

void LinkedList::addCommand(const std::string& command) {
    Node* newNode = new Node(command);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    current = tail;
}

std::string LinkedList::getPreviousCommand() {
    if (current == nullptr || current->prev == nullptr) {
        return "";
    }
    current = current->prev;
    return current->command;
}

std::string LinkedList::getNextCommand() {
    if (current == nullptr || current->next == nullptr) {
        return "";
    }
    current = current->next;
    return current->command;
}

#include "hashtable.h"
extern HashTable metadataTable;

std::string LinkedList::itihas() {
    Node* temp = head;
    if (temp == nullptr) {
        return "Bhai! Tumne koi commands nahi diye abhi!\n";
    }

    std::string result = "Bhai! Tumhare sab commands ki list aur unka istemal:\n";
    std::unordered_set<std::string> processedCommands;

    while (temp != nullptr) {
        std::string baseCommand = trim(temp->command.substr(0, temp->command.find(" ")));

        if (processedCommands.find(baseCommand) == processedCommands.end()) {
            int usageCount = metadataTable.getCommandCount(baseCommand);
            result += baseCommand + " - Istemal kiya gaya " + std::to_string(usageCount) + " baar\n";
            processedCommands.insert(baseCommand);
        }

        temp = temp->next;
    }

    return result;
}
