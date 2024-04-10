//
// Created by Luis carmona on 4/8/24.
//
#ifndef ASSIGNMENT1_460_AST_NODE_HPP
#define ASSIGNMENT1_460_AST_NODE_HPP
#include "../Token/Token.h"
#include "../SymbolTable/SymbolTable.h"
class AST_Node;
using ASTNodePtr = std::shared_ptr<AST_Node>;

class AST_Node {

  public:
    //constructor
    AST_Node(const Token& val);

    //returns the left child
    ASTNodePtr Left();

    //returns the right child
    ASTNodePtr Right();

    //returns the token value
    Token Value();

    //assign left child
    void addLeftChild(const ASTNodePtr & nodePtr);

    //assign the right child
    void addRightChild(const ASTNodePtr & nodePtr);

  private:
    ASTNodePtr leftChild;
    ASTNodePtr rightChild;
    Token value;
    SymTblPtr symbolTable;




};

#endif // ASSIGNMENT1_460_AST_NODE_HPP
