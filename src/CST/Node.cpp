
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

NodePtr Node::Left() {
    return leftChild;
}
NodePtr Node::Right() {
    return rightSibling;
}

Token Node::Value() {
    return value;
}