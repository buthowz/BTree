// SUjit Neupane sujitn@uw.edu
// 15 Jan 2018

// BinarySearchTree class
// Creates a BST to store values
// Uses BinaryNode which holds the data
// Uses templates to store any type of data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately
#include <algorithm>
#include <memory>

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() {
        // default constructor
}

// destructor, deletes pointers
template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree() {
        destructorHelper(rootPtr);
}

// recursive helper function for destructor
template<class ItemType>
void BinarySearchTree<ItemType>::destructorHelper(BinaryNode<ItemType>* 
                                subTreePtr) {
    if (subTreePtr) {
        destructorHelper(subTreePtr->getLeftChildPtr());
        destructorHelper(subTreePtr->getRightChildPtr());
        delete subTreePtr;
    }
}

// constructor takes root item
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem) {
    rootPtr = new BinaryNode<ItemType>(rootItem);
}

// copy constructor
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree
(const BinarySearchTree<ItemType>& bst) {
    rootPtr = copyTree(bst.rootPtr);
}

// recursive helper function for copy constructor
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::
copyTree(BinaryNode<ItemType>* oldTreeRootPtr) {
    BinaryNode<ItemType>* newTreePtr = nullptr;
    if (oldTreeRootPtr != nullptr) {
        // getting and copying to newTreePtr
        newTreePtr = new BinaryNode<ItemType>(oldTreeRootPtr->getItem());
        // going through both childs
        newTreePtr->setLeftChildPtr(copyTree(oldTreeRootPtr->getLeftChildPtr()));
        newTreePtr->setRightChildPtr(copyTree(oldTreeRootPtr->getRightChildPtr()));
    }
    return newTreePtr;  
}

// returns true if rootPtr is pointing to nullptr(empty tree)
template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const {
    return (!rootPtr); // rootPtr == nullptr
}

// gets height of the tree
template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const { 
    return getHeight(rootPtr);
}

// recursive helper function which gets height of the tree. Takes rootPtr of a
// tree as a parameter
template<class ItemType>
int BinarySearchTree<ItemType>::getHeight(BinaryNode<ItemType>* newRootPtr) 
                const {
    if (newRootPtr == nullptr) {
        return 0;
    }
    // adds 1 to whichever subtree has more subtrees to provide height of tree
    return 1 + max(getHeight(newRootPtr->getLeftChildPtr()), 
                                    getHeight(newRootPtr->getRightChildPtr()));
}

// returns the total numer of nodes in the tree
template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const {
    return getNumberOfNodes(rootPtr);
}

// recursive helper function to get total number of nodes
template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes
(BinaryNode<ItemType>* newRootPtr) const {
    if (newRootPtr == nullptr) {
        return 0;
    }
    // adds root + left child + right child
    return 1 + getNumberOfNodes(newRootPtr->getLeftChildPtr()) + 
                    getNumberOfNodes(newRootPtr->getRightChildPtr());
}

// item as a parameter, makes a newnode with the item and adds it to the tree
// adds to the right if item is bigger than root, adds to the left if smaller, 
// does not add duplicates.
template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& item) {    
    if (rootPtr == nullptr) {
        rootPtr = new BinaryNode<ItemType>(item);
        return true;
    } else {
        BinaryNode<ItemType>* current = rootPtr;
        bool inserted = false;
        while (inserted == false) {
            if (item == current->getItem()) {  // checks for duplicate entry
                return false;
            } else if (item < current->getItem()) {
                    if (current->getLeftChildPtr() == nullptr) {
                        current->setLeftChildPtr(new BinaryNode<ItemType>(item));
                        inserted = true;
                    }
                    else {
                        current = current->getLeftChildPtr();
                    }
            } else {  // if (item > current->getItem()), it goes towards right subtree
                if (current->getRightChildPtr() == nullptr) {
                             current->setRightChildPtr(new BinaryNode<ItemType>(item)); 
                    inserted = true;
                } else {
                        current = current->getRightChildPtr();
                    }
            }
        }
    }
    return true;
}

// clears the whole tree
template<class ItemType>
void BinarySearchTree<ItemType>::clear() {
    clear(rootPtr);
    rootPtr = NULL;
}

// recursive helper function to clear tree
template<class ItemType>
void BinarySearchTree<ItemType>::clear(BinaryNode<ItemType>* newRootPtr) {
    // Reference::
    // https://www.geeksforgeeks.org/write-a-c-program-to-delete-a-tree/
    if (newRootPtr == NULL) { 
    	return; 
    }
    clear (newRootPtr->getLeftChildPtr());
    clear (newRootPtr->getRightChildPtr());
    delete newRootPtr;
}

// checks for the content with the item provided, returns true if exists
template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& item) const {
    return contains(rootPtr, item);
}

// helper recursive function for contains
template<class ItemType>
bool BinarySearchTree<ItemType>::contains(BinaryNode<ItemType>* subTreePtr, 
        const ItemType& item) const {
    if (subTreePtr == NULL) {
        return false;
    } else if (subTreePtr->getItem() == item) {
        return true;
    } else {
        return contains(subTreePtr->getLeftChildPtr(), item) 
                        || contains(subTreePtr->getRightChildPtr(), item);
    }
}

// helper function for add
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::
placeNode(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr) {
    if (subTreePtr == nullptr) {
        return newNodePtr;
    } else if (subTreePtr->getItem() > newNodePtr->getItem()) {
            subTreePtr->setLeftChildPtr(placeNode(subTreePtr->getLeftChildPtr(), 
                                                        newNodePtr)); 
    } else {  // subTreeItem < newNodeItem
                    subTreePtr->setRightChildPtr(placeNode(subTreePtr->getRightChildPtr(), 
                                                        newNodePtr));
    }
    return subTreePtr;
}       // end placeNode

// inorderTraverse, where we visit leftChild, root and rightChild
template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const {
    inorder(visit, rootPtr);
}  // end inorder

// helper recursive function for inorderTraverse
template<class ItemType>
void BinarySearchTree<ItemType>::inorder(void visit(ItemType&), 
                                BinaryNode<ItemType>* treePtr) const {
    if (treePtr != nullptr) {
        inorder(visit, treePtr->getLeftChildPtr());
        ItemType item = treePtr->getItem();
        visit(item); 
        inorder(visit, treePtr->getRightChildPtr());
    }
}

// create dynamic array, copy all the items to the array
// and then read the array to re-create this tree
template<class ItemType>
void BinarySearchTree<ItemType>::rebalance() {
    int arraySize = getNumberOfNodes();
    ItemType* newArray = new ItemType[arraySize];
    toArray(newArray, 0, rootPtr);
    readTree(newArray, arraySize);
    delete[] newArray;
}

// helper recursive function to rebalance tree
// copies the values of this tree to an array provided
template<class ItemType>
int BinarySearchTree<ItemType>::toArray(ItemType arr[], int counter, 
                                BinaryNode<ItemType>* treePtr) const {
    if (treePtr == nullptr) {
    	return counter;
    }
    ItemType item = treePtr->getItem();
    arr[counter] = item;
    counter++;

    if (treePtr->getLeftChildPtr() != NULL) {
        counter = toArray(arr, counter, treePtr->getLeftChildPtr());
    }
    if (treePtr->getRightChildPtr() != NULL) {
        counter = toArray(arr, counter, treePtr->getRightChildPtr());
    }
    return counter;
}

// given an array of length n
// create this tree to have all items in that array
// with the minimum height
template<class ItemType>
bool BinarySearchTree<ItemType>::readTree(ItemType arr[], int n) {
    if (n < 0) {
        return false;
    }
    else if (n == 0) {
        clear();
        return true;
    }
    else { // (n > 0)
        clear();
        readTree(arr, 0, n - 1);
        return true;
    }
}

// Reference: https://www.geeksforgeeks.org/convert-normal-bst-balanced-bst/
// helper recursive function to readTree
template<class ItemType>
void BinarySearchTree<ItemType>::readTree(ItemType arr[], int first, int last)
{
    if (first > last) {
        return;
    }
    int mid = (first + last)/2;
    
    add(arr[mid]);
    readTree(arr, first, mid - 1);
    readTree(arr, mid + 1, last);
}

template<class ItemType>
void BinarySearchTree<ItemType>::displaySideways() const {
    sideways(rootPtr, 0);
}

template<class ItemType>
void BinarySearchTree<ItemType>::sideways(BinaryNode<ItemType>* current, 
                                int level) const {
    if (current != NULL) {
        level++;
        sideways(current->getRightChildPtr(), level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }

        cout << current->getItem() << endl;// display information of object
        sideways(current->getLeftChildPtr(), level);
    }
}

// == operator overloading to check if two bsts are equal
template<class ItemType>
bool BinarySearchTree<ItemType>::operator==
(const BinarySearchTree<ItemType>& other) const {
    if (other.rootPtr != nullptr && this->rootPtr != nullptr) {
        return equals(rootPtr, (other.rootPtr));
    }
    return false;
}

// helper recursive function for == operator overloading
template<class ItemType>
bool BinarySearchTree<ItemType>::equals
(const BinaryNode<ItemType>* firstRootPtr, 
        const BinaryNode<ItemType>* secondRootPtr) const {
    if (firstRootPtr == secondRootPtr) {
        return true;
    }
    return (firstRootPtr->getItem() == secondRootPtr->getItem()) &&
        equals((firstRootPtr->getLeftChildPtr()), 
                                        (secondRootPtr->getLeftChildPtr()))
        && equals((firstRootPtr->getRightChildPtr()), 
                                        (secondRootPtr->getRightChildPtr()));
}

// overloaded != operator
template<class ItemType>
bool BinarySearchTree<ItemType>::operator!=
(const BinarySearchTree<ItemType>& other) const {
    return !(*this == other);
}
