#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
using namespace std;
struct Node {
       string command;
    Node* next;
    Node* prev;

    Node(const string& cmd) : command(cmd), next(nullptr), prev(nullptr) {}
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void addCommand(const    string& command);
       string getPreviousCommand();
       string getNextCommand();
       string itihas();

private:
    Node* head;
    Node* tail;
    Node* current;
};

#endif
