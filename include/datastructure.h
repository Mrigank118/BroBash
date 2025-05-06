#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <string>
#include <map>
using namespace std;
struct TreeNode {
      string name;  
    TreeNode* parent;  
      map<  string, TreeNode*> children;  

    
    TreeNode(const   string& name, TreeNode* parent = nullptr) : name(name), parent(parent) {}
};


class DirectoryTree {
public:
    TreeNode* root;  
    TreeNode* current;  
      string currentPath;  
    DirectoryTree();

    
      string jaha();  
      string chalo(const   string& dirName);  
      string wapas();  
      string dikhao();  
      string banaoDir(const   string& dirName); 
      string khojo(const   string& fileName); 
      string getCurrentPath(); 

   
    ~DirectoryTree();

private:
    
    void deleteTree(TreeNode* node);  
    void populateTree(TreeNode* node, const   string& path);  
};

#endif
