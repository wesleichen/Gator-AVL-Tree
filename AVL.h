//
// Created by wesle on 10/4/2024.
//

#pragma once
#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H

#include <iostream>
#include <vector>

class BST
{
private:
    struct TreeNode
    {
        int height = 1;
        int balance = 0;
        int size = 1;
        std::string name;
        std::string gatorID;
        TreeNode *left;
        TreeNode *right;
        TreeNode(std::string NAME, std::string ID) :
                name(NAME), gatorID(ID), left(nullptr), right(nullptr) {}
    };

    TreeNode* root = nullptr;
    BST::TreeNode* helperInsert(TreeNode* helpRoot, std::string name, std::string gatorID);
    void helperInorder(TreeNode* helpRoot, bool& first);
    void helperPreorder(TreeNode* helpRoot, bool& first);
    void helperPostorder(TreeNode* helpRoot, bool& first);
    BST::TreeNode* rotateLeft(TreeNode* helpRoot);
    BST::TreeNode* rotateRight(TreeNode* helpRoot);
    int findHeight(TreeNode* helpRoot);
    int findSize(TreeNode* helpRoot);
    int findBalance(TreeNode* helpRoot);
    void helperSearchID(TreeNode* helpRoot, std::string gatorID);
    void helperSearchName(TreeNode* helpRoot, std::string name, bool& found);
    BST::TreeNode* helperRemoveID(TreeNode* helpRoot, std::string gatorID);
    void helperRemoveInorder(TreeNode* helpRoot, int find);
    void helperDeleteTree(TreeNode* helpRoot);

public:
    void searchID(std::string ID);
    void searchName(std::string name);
    void printLevelCount();
    void inorder();
    void preorder();
    void postorder();
    void insert(std::string name, std::string gatorID);
    void removeID(std::string gatorID);
    void removeInorder(std::string ID);
    void search(std::string string);
    ~BST(){
        helperDeleteTree(root);
    }
};

#endif //PROJECT1_AVL_H
