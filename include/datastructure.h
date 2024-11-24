#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <string>
#include <map>

// TreeNode represents a single node in the DirectoryTree.
struct TreeNode {
    std::string name;  // Name of the directory or file
    TreeNode* parent;  // Pointer to the parent node
    std::map<std::string, TreeNode*> children;  // Map of child nodes

    // Constructor for TreeNode
    TreeNode(const std::string& name, TreeNode* parent = nullptr) : name(name), parent(parent) {}
};

// DirectoryTree represents the structure of a directory hierarchy.
class DirectoryTree {
public:
    TreeNode* root;  // Root node of the directory tree
    TreeNode* current;  // Current directory pointer
    std::string currentPath;  // Current absolute path

    // Constructor to initialize the directory tree
    DirectoryTree();

    // Methods for directory navigation and management
    std::string jaha();  // Get current directory path
    std::string chalo(const std::string& dirName);  // Change to a specific directory
    std::string wapas();  // Move up to the parent directory
    std::string dikhao();  // List contents of the current directory
    std::string banaoDir(const std::string& dirName);  // Create a new directory
    std::string khojo(const std::string& fileName); 
    std::string getCurrentPath(); // Search for a file or directory

    // Destructor to clean up dynamically allocated memory
    ~DirectoryTree();

private:
    // Helper methods for internal operations
    void deleteTree(TreeNode* node);  // Recursively delete the tree
    void populateTree(TreeNode* node, const std::string& path);  // Populate the tree with the current directory structure
};

#endif
