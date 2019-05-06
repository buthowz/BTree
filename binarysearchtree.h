// Sujit Neupane sujitn@uw.edu
// 15 Jan 2018

// BinarySearchTree class
// Creates a BST to store values
// Uses BinaryNode which holds the data
// Uses templates to store any type of data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "binarynode.h"

using namespace std;

template<class ItemType>
class BinarySearchTree {
    public:
        // constructor, empty tree
        BinarySearchTree();
        // constructor, tree with root
        explicit BinarySearchTree(const ItemType& rootItem);
        // copy constructor
        BinarySearchTree(const BinarySearchTree<ItemType>& bst);
        // destructor
        virtual ~BinarySearchTree();
        // true if no nodes
        bool isEmpty() const;
        // 0 if empty, 1 if only root, otherwise
        // max height of subtrees + 1
        int getHeight() const;
        // number of nodes and data in tree
        int getNumberOfNodes() const;
        // add a new item
        // return true if successfull
        // false if item already in tree or some other reason to fail
        bool add(const ItemType& item);
        // true if item is in tree
        bool contains(const ItemType& item) const;
        // dispaly a sideways ascii representation of tree
        void displaySideways() const;
        // inorder traversal: left-root-right
        // takes a function that takes a single parameter of ItemType
        // the function can modify the data in tree, but the
        // tree structure is not changed
        void inorderTraverse(void visit(ItemType&)) const;
        // create dynamic array, copy all the items to the array
        // and then read the array to re-create this tree
        void rebalance();
        // delete all nodes in tree and set root to nullptr
        void clear();
        // given an array of length n
        // create this tree to have all items in that array
        // with the minimum height
        bool readTree(ItemType arr[], int n);
        // trees are equal if they have the same structure
        // AND the same item values at all the nodes
        bool operator==(const BinarySearchTree<ItemType> &) const;
        // not == to each other
        bool operator!=(const BinarySearchTree<ItemType> &) const;
    private:
        // root of the tree
        BinaryNode<ItemType>* rootPtr {nullptr};
        // add a new node, helper function for add
        BinaryNode<ItemType>* placeNode(BinaryNode<ItemType>* subTreePtr, 
                        BinaryNode<ItemType>* newNodePtr);
        // helper function for displaySideways to work recursively
        void sideways(BinaryNode<ItemType>* current, int level) const;
        // recursive function to find height of tree
        int getHeight(BinaryNode<ItemType>* newRootPtr) const;
        // recursive helper function to find the number of nodes
        int getNumberOfNodes(BinaryNode<ItemType>* newRootPtr) const;
        // recursive helper function to clear the tree
        void clear(BinaryNode<ItemType>* newRootPtr); 
        // recursive helper function for contains
        bool contains(BinaryNode<ItemType>* subTreePtr, 
                        const ItemType& item) const; 
        // recursive destrutor helper function
        void destructorHelper(BinaryNode<ItemType>* subTreePtr);
        // recursive helper function for copy constructor
        BinaryNode<ItemType>* copyTree(BinaryNode<ItemType>* oldTreeRootPtr); 
        // recursive helper function for == operator overloading
        bool equals(const BinaryNode<ItemType>* firstRootPtr, 
                        const BinaryNode<ItemType>* secondRootPtr) const;
        // helper recursive function for inorderTraverse
        void inorder(void visit(ItemType&), 
                        BinaryNode<ItemType>* treePtr) const;
        // helper recursive function for readTree
        void readTree(ItemType arr[], int first, int last);
        // copies the values of this tree to an array provided
        int toArray(ItemType arr[], int counter, 
                        BinaryNode<ItemType>* treePtr) const;
};
#include "binarysearchtree.cpp"

#endif // BINARYSEARCHTREE_H
