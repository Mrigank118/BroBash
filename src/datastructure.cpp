#include "datastructure.h"
#include <iostream>
#include <vector>
#include <unistd.h>
#include <dirent.h>
#include <stack>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>

using namespace std;

DirectoryTree::DirectoryTree() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        root = new TreeNode("/");
        currentPath = std::string(cwd);
        current = root;
        populateTree(root, currentPath);
    } else {
        root = new TreeNode("/");
        current = root;
        currentPath = "/";
    }
}
std::string DirectoryTree::khojo(const std::string& target) {
    std::stack<TreeNode*> stack;
    stack.push(root);

    while (!stack.empty()) {
        TreeNode* node = stack.top();
        stack.pop();

        // Check if the current node matches the target
        if (node->name == target) {
            // Build the full path
            std::string path;
            TreeNode* temp = node;

            while (temp != nullptr && temp != root) {
                path = "/" + temp->name + path;
                temp = temp->parent;
            }

            // Prepend the current path
            std::string fullPath = getCurrentPath() + path;

            return "Bhai! Mil gaya: " + fullPath;
        }

        // Push all child nodes onto the stack
        for (const auto& [childName, childNode] : node->children) {
            stack.push(childNode);
        }
    }

    // If the target is not found
    return "Bhai! Yeh nahi mila: " + target;
}

void DirectoryTree::populateTree(TreeNode* node, const string& path) {
    DIR* dir = opendir(path.c_str());
    if (dir == NULL) {
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (string(entry->d_name) == "." || string(entry->d_name) == "..") {
            continue;
        }

        string childPath = path + "/" + entry->d_name;
        node->children[entry->d_name] = new TreeNode(entry->d_name, node);

        populateTree(node->children[entry->d_name], childPath);
    }
    closedir(dir);
}

std::string DirectoryTree::jaha() {
    return "Bhai! Tum yeh directory mein ho: " + getCurrentPath();
}

std::string DirectoryTree::chalo(const std::string& dirName) {
    if (dirName == "..") {
        return wapas();
    }

    if (current->children.find(dirName) != current->children.end()) {
        current = current->children[dirName];
        currentPath += "/" + dirName;
        return "Bhai! Tum ab " + getCurrentPath() + " mein ho!";
    } else {
        return "Bhai! Yeh directory nahi mil rahi: " + dirName;
    }
}

std::string DirectoryTree::wapas() {
    if (current->parent != nullptr) {
        current = current->parent;

        size_t pos = currentPath.find_last_of("/");
        currentPath = currentPath.substr(0, pos);

        if (currentPath.empty()) {
            currentPath = "/";
        }
        return "Bhai! Tum ek level upar ho! Ab tum " + getCurrentPath() + " mein ho!";
    } else {
        return "Bhai! Tum root directory mein ho, upar nahi jaa sakte!";
    }
}

std::string DirectoryTree::dikhao() {
    if (current->children.empty()) {
        return "Bhai! Yeh directory khaali hai: " + getCurrentPath();
    }

    std::string output = "Bhai! Yeh directories aur files hain " + getCurrentPath() + " mein:\n";
    for (const auto& [name, node] : current->children) {
        output += "  " + name + "\n";
    }
    return output;
}

std::string DirectoryTree::banaoDir(const std::string& dirName) {
    std::string newPath = currentPath + "/" + dirName;
    if (mkdir(newPath.c_str(), 0755) == 0) {
        current->children[dirName] = new TreeNode(dirName, current);
        return "Bhai! Naya directory ban gaya: " + newPath;
    } else {
        return "Bhai! Directory nahi ban paya: " + dirName;
    }
}

std::string DirectoryTree::getCurrentPath() {
    return currentPath.empty() ? "/" : currentPath;
}

DirectoryTree::~DirectoryTree() {
    deleteTree(root);
}

void DirectoryTree::deleteTree(TreeNode* node) {
    for (auto& [name, child] : node->children) {
        deleteTree(child);
    }
    delete node;
}
