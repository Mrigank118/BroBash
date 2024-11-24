#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

struct Node {
    std::string command;
    Node* next;
    Node* prev;

    Node(const std::string& cmd) : command(cmd), next(nullptr), prev(nullptr) {}
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void addCommand(const std::string& command);
    std::string getPreviousCommand();
    std::string getNextCommand();
    std::string itihas();

private:
    Node* head;
    Node* tail;
    Node* current;
};

#endif
