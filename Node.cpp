#include "Node.h"
#include <iostream>

// Constructor 
Node::Node(const std::string& val) : value(val), leftChild(nullptr), rightChild(nullptr) {}

// Function to add a child node in the Left-Child Right-Sibling Tree
void Node::addChild(const NodePtr& child) {
    if (!leftChild) {
        leftChild = child; // If there's no child then make this node the left child
    } else {
        NodePtr current = leftChild;
        while (current->rightChild) { // Find the rightmost sibling
            current = current->rightChild;
        }
        current->rightChild = child; // Add the new child as the rightmost sibling
    }
}
