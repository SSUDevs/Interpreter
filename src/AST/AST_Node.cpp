//
// Created by Luis carmona on 4/8/24.
//

#include "AST_Node.hpp"
AST_Node::AST_Node(const Token &val): value(val),leftChild(nullptr),rightChild(nullptr),symbolTable(nullptr) {}

ASTNodePtr AST_Node::Left(){
    return leftChild;
}

ASTNodePtr AST_Node::Right(){
    return rightChild;
}
Token AST_Node::Value(){
    return value;
}
void AST_Node::addLeftChild(const ASTNodePtr &nodePtr) {

    leftChild = nodePtr;
}
void AST_Node::addRightChild(const ASTNodePtr &nodePtr) {
    rightChild= nodePtr;
}

