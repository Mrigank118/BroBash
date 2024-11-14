#include "linkedlist.h"
#include <iostream>

// Constructor: Initializes an empty linked list
LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    current = nullptr;
}

// Destructor: Clears the linked list
LinkedList::~LinkedList() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
}

// Add a command to the linked list (at the end)
void LinkedList::addCommand(const std::string& command) {
    Node* newNode = new Node(command);
    if (tail == nullptr) {
        head = tail = newNode;  // First node in the list
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    current = tail;  // Set the current pointer to the most recent command
}

// Get the previous command in the list
std::string LinkedList::getPreviousCommand() {
    if (current == nullptr || current->prev == nullptr) {
        return "";  // No previous command
    }
    current = current->prev;
    return current->command;
}

// Get the next command in the list
std::string LinkedList::getNextCommand() {
    if (current == nullptr || current->next == nullptr) {
        return "";  // No next command
    }
    current = current->next;
    return current->command;
}
