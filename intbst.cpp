// intbst.cpp
// Implements class IntBST
// YOUR BRANDON SO, 4/24/26

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr; // initializes to null
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n == nullptr){ // deals with empty case
        return;
    }

    clear(n->left); // recusrse through the left subtree

    
    clear(n->right); //recurse through the right subtree

    
    delete n; // delete the node
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (n == nullptr) { // deals with empty case
        root = new Node(value); // creates new node and exits
        return true;
    }

    if (n -> info == value){ // checks if the value is already in the tree
        return false;
    }

    if (n -> info > value){ // checks if the current node is bigger than value
        if (n->left == nullptr) { // if left node is empty
            n->left = new Node(value); // creates new node 
            n -> left -> parent = n; // sets the parent to the previous node
            return true;
        }

        return insert(value, n->left); // Recurse if path isn't empty

    }

    else{ // checks if the current node is bigger than value
        if (n -> right == nullptr){ // checks if the right node is empty
            n -> right = new Node(value); //creates new node
            n -> right -> parent = n; // sets the parent node to the previous node
            return true;
        }

        return insert(value, n -> right); // recurse if path isn't empty

    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n == nullptr){
        return;
    }

    cout << n -> info << " "; // print out the root node

    printPreOrder(n -> left); // traverse the left subtree

    printPreOrder(n -> right); // traverse the right subtree next
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if (n == nullptr){ // deal with empty tree
        return;
    }

    printInOrder(n -> left); // traverse left subtree

    cout << n->info << " "; // print out current node

    printInOrder(n -> right); // traverse right subtree
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n == nullptr){ // deal with empty tree
        return;
    }

    printPostOrder(n -> left); // traverse left subtree

    printPostOrder(n -> right); // traverse right subtree

    cout << n->info << " "; // print out current node
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (n == nullptr){ // deals with empty tree
        return 0;
    }

    int total = n -> info; // initializes with root 
    total += sum(n -> left) + sum(n -> right); // recurses through every element and adds to sum
    

    return total;
}

// return count of values
int IntBST::count() const {
    return count(root); 
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (n == nullptr){ // deals with empty tree
        return 0;
    }

    int num = 0; // initializes count var

    num = 1 + count(n -> left) + count(n -> right); // recurses through every node in tree

    return num;
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (n == nullptr) { // deals with empty tree
        return nullptr;
    }

    if (n -> info == value) { // returns value if found
        return n;
    }

    if (value < n -> info) { // recurses into the left subtree if value is smaller
        return getNodeFor(value, n -> left);
    } 
    
    else { // otherwise recurses into the right subtree
        return getNodeFor(value, n -> right);
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    bool val = (getNodeFor(value, root) != nullptr); // turns the output into a boolean value
    return val;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* n = getNodeFor(value, root); // Gets the node you are trying to find the predecessor of 

    if (n == nullptr) { // deals with empty tree
        return nullptr;
    }


    if (n->left != nullptr) { // if there is a left subtree
        Node* temp = n->left; // go to the left value
        while (temp->right != nullptr) { // recurse as far as you can into the right side 
            temp = temp->right; 
        }
        return temp;
    }

    else {
        Node* p = n -> parent; // otherwise recurses up the tree until n isn't the left child
        while(p != nullptr && p -> left == n){
            n = p;
            p = p -> parent;
        }

        return p;

    }
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* prevNode = getPredecessorNode(value); 

    if (prevNode == nullptr) { // deals with the case where nothing is found
        return 0; 
    }

    return prevNode -> info;
}

IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* n = getNodeFor(value, root); // // Gets the node you are trying to find the successor of 


    if (n == nullptr) { // deals with empty case
        return nullptr;
    }

    if (n->right != nullptr) { // if there is a right subtree
        Node* temp = n->right; // go to the right value
        while (temp->left != nullptr) { // recurses as far into the left subtree as possible
            temp = temp->left;
        }
        return temp;
    }

    else {
        Node* p = n -> parent; // otherwise recurses up the tree until n isn't the right child
        while(p != nullptr && p -> right == n){
            n = p;
            p = p -> parent;
        }

        return p;

    }
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* nextNode = getSuccessorNode(value);
    
    if (nextNode == nullptr) { // deals with the case where nothing is found
        return 0; 
    }
    return nextNode -> info;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* n = getNodeFor(value, root); // gets the node you are trying to remove
    if (n == nullptr){ // checks if the value exists in the tree
        return false;
    }

    if (n == root) { // if n is the root 
        if (n -> left != nullptr) { // if the root has a left child
            root = n -> left; // makes the root the left subtree
            root -> parent = nullptr; // makes the new root point to nothing 
        } 
        
        else if (n -> right != nullptr) { // if the root has a right child
            root = n -> right; // makes the root the right subtree
            root -> parent = nullptr; // makes the new root point to nothing
        } 
        
        else {
            root = nullptr;
        } 
        delete n; // deletes node
        return true;
    }
    
    if ((n -> left != nullptr) && (n -> right != nullptr)){ // if node has two children
        Node* succ = getSuccessorNode(value); // get the successor
        n -> info = succ -> info; // replace the node with the successor
        return remove(succ -> info); // recurse until theres only one child
    }

    Node* parent = n->parent; // makes a pointer to the parent of the node

    if ((n -> left == nullptr) && (n -> right == nullptr)){ // if node has no children
        if (parent -> left == n){ // checks if the node is on the left
            parent -> left = nullptr; // sets it to null
        }

        else {
            parent -> right = nullptr; // otherwise sets the right node to null
        }
    }

    else if (n -> left != nullptr) { // Node only has a left child
        if (parent -> left == n){ // if the child is the left node
            parent -> left = n -> left; // sets the parents left to n's left subtree
        }
        else{
            parent -> right = n -> left; // otherwise points parent's right to n's left subtree
        }
        n -> left -> parent = parent; // Update the child's parent pointer to the grandparent
    } 

    else { // Node only has a right child
        if (parent -> left == n) { // if node is parent's left child
            parent -> left = n -> right; // point parent's left to n's right child
        }

        else{ // Node only has a left child 
            parent -> right = n -> right; // points to parent's right to n's right child
        }
        n -> right -> parent = parent; // Update the child's parent pointer to the grandparent
    }

    return true;
}
