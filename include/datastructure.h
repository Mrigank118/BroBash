#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <string>
#include <map>

struct TreeNode {
    std::string name;  
    TreeNode* parent;  
    std::map<std::string, TreeNode*> children;  

    
    TreeNode(const std::string& name, TreeNode* parent = nullptr) : name(name), parent(parent) {}
};


class DirectoryTree {
public:
    TreeNode* root;  
    TreeNode* current;  
    std::string currentPath;  
    DirectoryTree();

    
    std::string jaha();  
    std::string chalo(const std::string& dirName);  
    std::string wapas();  
    std::string dikhao();  
    std::string banaoDir(const std::string& dirName); 
    std::string khojo(const std::string& fileName); 
    std::string getCurrentPath(); 

   
    ~DirectoryTree();

private:
    
    void deleteTree(TreeNode* node);  
    void populateTree(TreeNode* node, const std::string& path);  
};

#endif
