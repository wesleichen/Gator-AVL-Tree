//
// Created by wesle on 10/4/2024.
//

#include <iostream>
#include <vector>

#include "AVL.h"


// Removes "" from parsing.
std::string cleanName(std::string name){
    return name.substr(1,name.length()-2);
}

// Checks if valid name
bool isValidName(const std::string& name) {
    for (char c : name) {
        if (!std::isalpha(c) && !std::isspace(c)) {
            return false;
        }
    }
    return true;
}

// Checks if valid ID of 8 digits
bool isValidID(std::string gatorID){
    if (gatorID.length() != 8) {
        return false;
    }
    for (char c : gatorID) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

// es for the student with the given ID, uses
// efficient O(log(n)) search.
void BST::helperSearchID(TreeNode* helpRoot, std::string ID){
    if (helpRoot == nullptr)
        std::cout << "unsuccessful" << std::endl;
    else if (ID == helpRoot->gatorID)
        std::cout << helpRoot->name << std::endl;
    else if (stoi(ID) < stoi(helpRoot->gatorID))
        helperSearchID(helpRoot->left, ID);
    else
        helperSearchID(helpRoot->right, ID);
}

// Searches for ID
void BST::searchID(std::string ID){
    helperSearchID(root, ID);
}

// Searches for names, if found, prints out the respective ID's in pre-order.
// If none are found, the flag found is never changed to true, so the
// searchName function prints "unsuccessful".
void BST::helperSearchName(BST::TreeNode *helpRoot, std::string name, bool &found){
    if (helpRoot == nullptr){
        return;
    }
    else if (name == helpRoot->name){
        std::cout << helpRoot->gatorID << std::endl;
        found = true;
    }
    helperSearchName(helpRoot->left, name, found);
    helperSearchName(helpRoot->right, name, found);
}

// Search for name
void BST::searchName(std::string name){
    bool found = false;
    helperSearchName(root, name, found);
    if (!found)
    {
        std::cout << "unsuccessful" << std::endl;
    }
}

// Determines whether to search for ID or Name
void BST::search(std::string string){
    if (isValidID(string)){
        searchID(string);
    }
    else
    {
        string = cleanName(string);
        if (isValidName(string))
        {
            searchName(string);
        }
        else{
            std::cout << "unsuccessful" << std::endl;
        }
    }
}


// Prints the level count (height) of a tree
// by using the root's height or 0 if the root is null.
void BST::printLevelCount()
{
    if (root == nullptr)
        std::cout <<  0 << std::endl;
    else
        std::cout << root->height << std::endl;
}

// Returns height by returning 0 if null,
// or the node's height value if not.
int BST::findHeight(BST::TreeNode *helpRoot)
{
    if (helpRoot == nullptr)
        return 0;
    else
        return helpRoot->height;
}

// Returns size by returning 0 if null,
// of the node's size value if not.
// Size is defined as the combined number of non-null nodes in the
// left and right subtrees of the node including the node itself.
int BST::findSize(BST::TreeNode *helpRoot)
{
    if (helpRoot == nullptr)
        return 0;
    else
        return helpRoot->size;
}

// Returns the balance by subtracting the right height from
// the left height of the subtrees.
int BST::findBalance(BST::TreeNode *helpRoot)
{
    if (helpRoot == nullptr)
        return 0;
    else
        return findHeight(helpRoot->left) - findHeight(helpRoot->right);
}

// From 4 - Balanced Trees from class slides
BST::TreeNode* BST::rotateLeft(BST::TreeNode* helpRoot)
{
    BST::TreeNode* grandchild = helpRoot->right->left;
    BST::TreeNode* newParent = helpRoot->right;
    newParent->left = helpRoot;
    helpRoot->right = grandchild;

    // Update Heights/Size
    helpRoot->height = std::max(findHeight(helpRoot->left), findHeight(helpRoot->right)) + 1;
    newParent->height = std::max(findHeight(newParent->left), findHeight(newParent->right)) + 1;
    helpRoot->size = findSize(helpRoot->left) + findSize(helpRoot->right) + 1;
    newParent->size = findSize(newParent->left) + findSize(newParent->right) + 1;
    return newParent;
}

// From 4 - Balanced Trees from class slides
BST::TreeNode* BST::rotateRight(BST::TreeNode* helpRoot)
{
    BST::TreeNode* grandchild = helpRoot->left->right;
    BST::TreeNode* newParent = helpRoot->left;
    newParent->right = helpRoot;
    helpRoot->left = grandchild;

    // Update Heights/Size
    helpRoot->height = std::max(findHeight(helpRoot->left), findHeight(helpRoot->right)) + 1;
    newParent->height = std::max(findHeight(newParent->left), findHeight(newParent->right)) + 1;
    helpRoot->size = findSize(helpRoot->left) + findSize(helpRoot->right) + 1;
    newParent->size = findSize(newParent->left) + findSize(newParent->right) + 1;
    return newParent;
}

// Method from 4 - Balanced Trees class slides
BST::TreeNode* BST::helperInsert(TreeNode* helpRoot, std::string name, std::string gatorID)
{
    // Attempts to insert the ID, if duplicate it is rejected.
    if (helpRoot == nullptr){
        std::cout << "successful" << std::endl;
        return new TreeNode(name, gatorID);
    }
    else if (gatorID == helpRoot->gatorID){
        std::cout << "unsuccessful" << std::endl;
        return helpRoot;
    }
    else if (stoi(gatorID) < stoi(helpRoot->gatorID))
        helpRoot->left = helperInsert(helpRoot->left, name, gatorID);
    else
        helpRoot->right = helperInsert(helpRoot->right, name, gatorID);

    // find height here along with size/balance
    helpRoot->height = std::max(findHeight(helpRoot->left), findHeight(helpRoot->right)) + 1;
    helpRoot->size = findSize(helpRoot->left) + findSize(helpRoot->right) + 1;
    helpRoot->balance = findBalance(helpRoot);

    // Conduct balancing.
    if (helpRoot->balance > 1){
        if (findBalance(helpRoot->left) > 0){
            return rotateRight(helpRoot);
        }
        else{
            helpRoot->left = rotateLeft(helpRoot->left);
            return rotateRight(helpRoot);
        }
    }
    else if (helpRoot->balance < -1){
        if (findBalance(helpRoot->right) < 0){
            return rotateLeft(helpRoot);
        }
        else{
            helpRoot->right = rotateRight(helpRoot->right);
            return rotateLeft(helpRoot);
        }
    }
    // if tree right heavy -> if right left heavy, RL / else L
    // if tree left heavy -> if left right heavy, LR / else R


    return helpRoot;
}

// Begins the insertion of an element.
void BST::insert(std::string name, std::string gatorID)
{
    // checks if input is good to insert
    name = cleanName(name);
    if (isValidName(name)){
        if (isValidID(gatorID)){
            this->root = helperInsert(this->root, name, gatorID);
        }
        else{
            std::cout << "unsuccessful" << std::endl;
        }
    }
    else
        std::cout << "unsuccessful" << std::endl;
}

// Removes based on ID, in log(n) time by using binary search
BST::TreeNode* BST::helperRemoveID(BST::TreeNode *helpRoot, std::string gatorID){
    if (helpRoot == nullptr){
        std::cout << "unsuccessful" << std::endl;
        return helpRoot;
    }
    else if (stoi(gatorID) < stoi(helpRoot->gatorID))
        helpRoot->left = helperRemoveID(helpRoot->left, gatorID);
    else if (stoi(gatorID) > stoi(helpRoot->gatorID))
        helpRoot->right = helperRemoveID(helpRoot->right, gatorID);
    else{
        // Cases where there is 0 or 1 children
        std::cout << "successful" << std::endl;
        if (helpRoot->left == nullptr){
            TreeNode* hold = helpRoot->right;
            delete helpRoot;
            helpRoot = nullptr;
            return hold;
        }
        else if (helpRoot->right == nullptr){
            TreeNode* hold = helpRoot->left;
            delete helpRoot;
            helpRoot = nullptr;
            return hold;
        }
        // Case where there are two children
        TreeNode* parent = nullptr;
        TreeNode* successor = root->right;

        // Finding inorder successor, reassigning parent node to not lose connecction
        while (successor->left != nullptr){
            parent = successor;
            successor = successor->left;
        }

        // Assigning nodes
        if (parent != nullptr){
            parent->left = successor->right;
        }
        else{
            helpRoot->right = successor->right;
        }

        // Replacement
        helpRoot->name = successor->name;
        helpRoot->gatorID = successor->gatorID;
        delete successor;
    }

    if (root == nullptr){
        return root;
    }

    // Updating heights/balances/sizes
    helpRoot->height = std::max(findHeight(helpRoot->left), findHeight(helpRoot->right)) + 1;
    helpRoot->size = findSize(helpRoot->left) + findSize(helpRoot->right) + 1;
    helpRoot->balance = findBalance(helpRoot);

    // Conduct balancing.
    if (helpRoot->balance > 1){
        if (findBalance(helpRoot->left) > 0){
            return rotateRight(helpRoot);
        }
        else{
            helpRoot->left = rotateLeft(helpRoot->left);
            return rotateRight(helpRoot);
        }
    }
    else if (helpRoot->balance < -1){
        if (findBalance(helpRoot->right) < 0){
            return rotateLeft(helpRoot);
        }
        else{
            helpRoot->right = rotateRight(helpRoot->right);
            return rotateLeft(helpRoot);
        }
    }

    return helpRoot;
}

void BST::removeID(std::string ID){
    // checks is ID is valid, then attempts to remove
    if (isValidID(ID)){
        helperRemoveID(this->root, ID);
    }
    else{
        std::cout << "unsuccessful" << std::endl;
    }
}

// find is now the n + 1th inorder node.
// Using size of a node to track which node is the n + 1th inorder.
void BST::helperRemoveInorder(BST::TreeNode *helpRoot, int find){
    if (helpRoot == nullptr){
        std::cout << "unsuccessful" << std::endl;
        return;
    }
    int leftSize = findSize(helpRoot->left);
    if (find == (leftSize + 1))
        helperRemoveID(this->root, helpRoot->gatorID);
    else if (find < (leftSize + 1))
        helperRemoveInorder(helpRoot->left, find);
    else // this recursive call lets the search go rightwards
        helperRemoveInorder(helpRoot->right, find - (leftSize + 1));
}

// Checks if valid input, then attempts removal
void BST::removeInorder(std::string position){
    for (char c : position) {
        if (!std::isdigit(c)) {
            std::cout << "unsuccessful" << std::endl;
            return;
        }
    }
    helperRemoveInorder(this->root, stoi(position) + 1);
}

// From Template Code
// Similar thought process for post and pre-order later,
// the first run node has no comma, but every node after
// is marked asd being !first, so a comma and a space ", "
// is inserted before the name is written.
void BST::helperInorder(BST::TreeNode* helpRoot, bool& first)
{
    if(helpRoot == nullptr)
        std::cout << "";
    else
    {
        helperInorder(helpRoot->left, first);

        if (!first){
            std::cout << ", ";
        }
        else{
            first = false;
        }

        std::cout << helpRoot->name;

        helperInorder(helpRoot->right, first);
    }
}

void BST::helperPreorder(BST::TreeNode* helpRoot, bool& first)
{
    if(helpRoot == nullptr)
        std::cout << "";
    else
    {
        if (!first){
            std::cout << ", ";
        }
        else{
            first = false;
        }

        std::cout << helpRoot->name;

        helperPreorder(helpRoot->left, first);

        helperPreorder(helpRoot->right, first);
    }
}

void BST::helperPostorder(BST::TreeNode* helpRoot, bool& first)
{
    if(helpRoot == nullptr)
        std::cout << "";
    else
    {
        helperPostorder(helpRoot->left, first);
        helperPostorder(helpRoot->right, first);

        if (!first){
            std::cout << ", ";
        }
        else{
            first = false;
        }

        std::cout << helpRoot->name;
    }
}

// Left, Node, Right
void BST::inorder()
{
    bool first = true;
    helperInorder(this->root, first);
    std::cout << std::endl;
}

// Node, Left, Right
void BST::preorder()
{
    bool first = true;
    helperPreorder(this->root, first);
    std::cout << std::endl;
}

// Left, Right, Node
void BST::postorder()
{
    bool first = true;
    helperPostorder(this->root, first);
    std::cout << std::endl;
}

// cleans up memory after all operations are complete
void BST::helperDeleteTree(BST::TreeNode* helpRoot){
    if (helpRoot == nullptr){
        return;
    }
    helperDeleteTree(helpRoot->left);
    helperDeleteTree(helpRoot->right);
    delete helpRoot;
}