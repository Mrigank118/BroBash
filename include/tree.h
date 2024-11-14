#ifndef TREE_H
#define TREE_H

#include <string>
#include <map>

struct TreeNode {
    std::string name;
    std::map<std::string, TreeNode*> children;

    TreeNode(const std::string& n) : name(n) {}
};

class FileSystemTree {
private:
    TreeNode* root;
public:
    FileSystemTree();
    void addFile(const std::string& path);
    void displayFiles(TreeNode* node, int depth = 0);
    TreeNode* getRoot() { return root; }
};

#endif
