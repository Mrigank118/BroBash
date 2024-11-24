// linkedlist.h

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

// Linked List Node structure
struct Node {
    std::string command;
    Node* next;
    Node* prev; // Add this line for previous pointer

    Node(const std::string& cmd) : command(cmd), next(nullptr), prev(nullptr) {}
};

class LinkedList {
public:
    LinkedList(); // Constructor
    ~LinkedList(); // Destructor

    // Add a new command to the linked list
    void addCommand(const std::string& command);

    // Get the previous command in the list
    std::string getPreviousCommand();

    // Get the next command in the list
    std::string getNextCommand();

    // Return a string containing the history of commands
    std::string itihas(); // Corrected return type

private:
    Node* head;   // Head pointer (first node)
    Node* tail;   // Tail pointer (last node)
    Node* current; // Pointer to the current command
};

#endif // LINKEDLIST_H
