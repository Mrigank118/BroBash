#include "linkedlist.h"
#include <iostream>
#include <unordered_set>  // Add this at the top
#include "commands.h"

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

#include "hashtable.h"
extern HashTable metadataTable;
std::string LinkedList::itihas() {
    Node* temp = head;
    if (temp == nullptr) {
        return "Bhai! Tumne koi commands nahi diye abhi!\n";
    }

    std::string result = "Bhai! Tumhare sab commands ki list aur unka istemal:\n";
    std::unordered_set<std::string> processedCommands;  // Avoid duplicates

    while (temp != nullptr) {
        std::string baseCommand = trim(temp->command.substr(0, temp->command.find(" ")));

        // Only process each command once
        if (processedCommands.find(baseCommand) == processedCommands.end()) {
            int usageCount = metadataTable.getCommandCount(baseCommand);  // Get the count
            result += baseCommand + " - Istemal kiya gaya " + std::to_string(usageCount) + " baar\n";
            processedCommands.insert(baseCommand);  // Mark as processed
        }

        temp = temp->next;
    }

    return result;
}
/*

### **3. Tree**
- **Commands**:
  1. **`jaha`** (pwd)  
     - Functionality: Get the current directory path.  
     - Data Structure Usage: Traverse the `DirectoryTree` to construct the path from the root to the current node.  

  2. **`dikhao`** (ls)  
     - Functionality: List files and directories in the current folder.  
     - Data Structure Usage: Iterate over the children of the current directory node.

  3. **`chalo <path>`** (cd)  
     - Functionality: Change directory to a specific folder.  
     - Data Structure Usage: Traverse the `DirectoryTree` to update the current directory pointer.

  4. **`wapas`** (cd ..)  
     - Functionality: Navigate to the parent directory.  
     - Data Structure Usage: Use the `parent` pointer in the tree to move up one level.

  5. **`banaoDir <directory>`** (mkdir)  
     - Functionality: Create a new directory.  
     - Data Structure Usage: Add a new node to the `DirectoryTree` as a child of the current node.

  6. **`khojo <filename>`** (find)  
     - Functionality: Search for a file or directory.  
     - Data Structure Usage: Perform DFS or BFS traversal on the `DirectoryTree`.

---

### **4. Queue**
- **Commands**:
  1. **`kamDekho <filename>`** (head)  
     - Functionality: Display the first N lines of a file.  
     - Data Structure Usage: Enqueue lines as the file is read; dequeue and display the first N.

  2. **`antDekho <filename>`** (tail)  
     - Functionality: Display the last N lines of a file.  
     - Data Structure Usage: Maintain a fixed-size queue to hold the last N lines.

  3. **`dikhaiDe`** (top)  
     - Functionality: Display the most resource-intensive running processes.  
     - Data Structure Usage: Use the queue to manage and prioritize processes.

---

### **5. Stack**
- **Commands**:
  1. **`wapas`** (cd .. with history)  
     - Functionality: Navigate up one directory and manage navigation history.  
     - Data Structure Usage: Push directories visited by `chalo` onto the stack; pop the stack for `wapas`.

---

### **6. Vector/Array**
- **Commands**:
  1. **`dikhao`** (ls)  
     - Functionality: Temporarily store the list of files and directories for iteration.  
     - Data Structure Usage: Store directory contents as a vector for easy traversal.

  2. **`pehchano`** (whoami)  
     - Functionality: Retrieve the logged-in user's name.  
     - Data Structure Usage: Use a string (simple array of characters).

  3. **`kyaDekho`** (df)  
     - Functionality: Show disk usage.  
     - Data Structure Usage: Store data block details in a vector for formatted output.

---

### **7. Heap**
- **Commands**:
  1. **`dikhaiDe`** (top)  
     - Functionality: Retrieve the most resource-intensive process.  
     - Data Structure Usage: Use a max-heap to efficiently fetch the top process.

---

This organization ensures each command is implemented with the most suitable data structure for efficiency and clarity in your **Bhai Lang Terminal**!Here’s the **Bhai Lang commands** grouped by the **data structure** used in their implementation:

---

### **1. Linked List**
- **Commands**:
  1. **`itihas`** (history)  
     - Functionality: Stores and navigates through the history of executed commands.  
     - Data Structure Usage: Each command is a node in the linked list for sequential navigation.

---

### **2. Hash Table**
- **Commands**:
  1. **`banao <filename>`** (touch)  
     - Functionality: Create a file and store its metadata.  
     - Data Structure Usage: Store file metadata (size, timestamp, path) in the hash table.  

  2. **`jaane <filename>`** (file info/stat)  
     - Functionality: Fetch detailed file metadata.  
     - Data Structure Usage: Retrieve metadata from the hash table.

  3. **`mitao <filename>`** (rm)  
     - Functionality: Delete a file and remove its metadata.  
     - Data Structure Usage: Remove file metadata from the hash table.

  4. **`dhoondo <pattern>`** (grep)  
     - Functionality: Search for a pattern in a file.  
     - Data Structure Usage: Store and index occurrences (line numbers, positions) in the hash table.

---

### **3. Tree**
- **Commands**:
  1. **`jaha`** (pwd)  
     - Functionality: Get the current directory path.  
     - Data Structure Usage: Traverse the `DirectoryTree` to construct the path from the root to the current node.  

  2. **`dikhao`** (ls)  
     - Functionality: List files and directories in the current folder.  
     - Data Structure Usage: Iterate over the children of the current directory node.

  3. **`chalo <path>`** (cd)  
     - Functionality: Change directory to a specific folder.  
     - Data Structure Usage: Traverse the `DirectoryTree` to update the current directory pointer.

  4. **`wapas`** (cd ..)  
     - Functionality: Navigate to the parent directory.  
     - Data Structure Usage: Use the `parent` pointer in the tree to move up one level.

  5. **`banaoDir <directory>`** (mkdir)  
     - Functionality: Create a new directory.  
     - Data Structure Usage: Add a new node to the `DirectoryTree` as a child of the current node.

  6. **`khojo <filename>`** (find)  
     - Functionality: Search for a file or directory.  
     - Data Structure Usage: Perform DFS or BFS traversal on the `DirectoryTree`.

---

### **4. Queue**
- **Commands**:
  1. **`kamDekho <filename>`** (head)  
     - Functionality: Display the first N lines of a file.  
     - Data Structure Usage: Enqueue lines as the file is read; dequeue and display the first N.

  2. **`antDekho <filename>`** (tail)  
     - Functionality: Display the last N lines of a file.  
     - Data Structure Usage: Maintain a fixed-size queue to hold the last N lines.

  3. **`dikhaiDe`** (top)  
     - Functionality: Display the most resource-intensive running processes.  
     - Data Structure Usage: Use the queue to manage and prioritize processes.

---

### **5. Stack**
- **Commands**:
  1. **`wapas`** (cd .. with history)  
     - Functionality: Navigate up one directory and manage navigation history.  
     - Data Structure Usage: Push directories visited by `chalo` onto the stack; pop the stack for `wapas`.

---

### **6. Vector/Array**
- **Commands**:
  1. **`dikhao`** (ls)  
     - Functionality: Temporarily store the list of files and directories for iteration.  
     - Data Structure Usage: Store directory contents as a vector for easy traversal.

  2. **`pehchano`** (whoami)  
     - Functionality: Retrieve the logged-in user's name.  
     - Data Structure Usage: Use a string (simple array of characters).

  3. **`kyaDekho`** (df)  
     - Functionality: Show disk usage.  
     - Data Structure Usage: Store data block details in a vector for formatted output.

---

### **7. Heap**
- **Commands**:
  1. **`dikhaiDe`** (top)  
     - Functionality: Retrieve the most resource-intensive process.  
     - Data Structure Usage: Use a max-heap to efficiently fetch the top process.

---

This organization ensures each command is implemented with the most suitable data structure for efficiency and clarity in your **Bhai Lang Terminal**!*/