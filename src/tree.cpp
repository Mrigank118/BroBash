#include "tree.h"
#include <iostream>

FileSystemTree::FileSystemTree() {
    root = new TreeNode("root");
}

void FileSystemTree::addFile(const std::string& path) {
    TreeNode* current = root;
    std::string dir = path;

    if (current->children.find(dir) == current->children.end()) {
        current->children[dir] = new TreeNode(dir);
    }
}

void FileSystemTree::displayFiles(TreeNode* node, int depth) {
    for (const auto& child : node->children) {
        std::cout << std::string(depth, ' ') << child.first << "\n";
        displayFiles(child.second, depth + 1);
    }
}
