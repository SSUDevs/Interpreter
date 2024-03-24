#include "Node.h"
#include <iostream>

// Constructor 
Node::Node(const Token& val) : value(val), leftChild(nullptr), rightSibling(nullptr) {}

// assign left child
void Node::addLeftChild(const NodePtr& nodePtr) {
	leftChild = nodePtr;
}

// assign right sibling
void Node::addRightSibling(const NodePtr& nodePtr) {
	rightSibling = nodePtr;
}

// Function to add a child node in the Left-Child Right-Sibling Tree
//void Node::addConnection(const NodePtr& child) {
//    if (!leftChild) {
//        leftChild = child; // If there's no child then make this node the left child
//    }
//    else {
//        NodePtr current = leftChild;
//        while (current->rightSibling) { // Find the rightmost sibling
//            current = current->rightSibling;
//        }
//        current->rightSibling = child; // Add the new child as the rightmost sibling
//    }
//}
