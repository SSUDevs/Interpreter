//
// Created by Luis carmona on 4/8/24.
//

#ifndef ASSIGNMENT1_460_AST_HPP
#define ASSIGNMENT1_460_AST_HPP
#include "AST_Node.hpp"
#include "../CST/Node.h"
class AST {
  public:

    AST();

    void parse(NodePtr *Croot);

    AST_Node inToPostfix_Integer();
    AST_Node inToPostfix_Bool();


  private:
    AST_Node *root;


};

#endif // ASSIGNMENT1_460_AST_HPP
