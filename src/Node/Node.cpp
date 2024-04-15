#include "Node.h"
#include <iostream>

// Constructor
Node::Node(const Token &val, Type type)
    : value(val), nodeType(type), leftChild(nullptr), rightSibling(nullptr) {}

// assign left child
void Node::addLeftChild(const NodePtr &nodePtr) { leftChild = nodePtr; }

// assign right sibling
void Node::addRightSibling(const NodePtr &nodePtr) { rightSibling = nodePtr; }

NodePtr Node::Left() { return leftChild; }
NodePtr Node::Right() { return rightSibling; }

Token Node::Value() { return value; }

void Node::setSemanticType(Type newType) { nodeType = newType; }
Node::Type Node::getSemanticType() const { return nodeType; }

std::string Node::semanticTypeToString(Type type) {
    switch (type) {
    case Type::DECLARATION:
        return "DECLARATION";
    case Type::ASSIGNMENT:
        return "ASSIGNMENT";
    case Type::BEGIN_BLOCK:
        return "BEGIN BLOCK";
    case Type::END_BLOCK:
        return "END BLOCK";
    case Type::IF:
        return "IF";
    case Type::ELSE:
        return "ELSE";
    case Type::FOR:
        return "FOR";
    case Type::WHILE:
        return "WHILE";
    case Type::PRINTF:
        return "PRINTF";
    case Type::RETURN:
        return "RETURN";
    case Type::OTHER:
        return "";
    default:
        return "INVALID_TYPE";
    }
}