//
// Created by Luis carmona on 4/8/24.
//

#ifndef ASSIGNMENT1_460_AST_HPP
#define ASSIGNMENT1_460_AST_HPP
#include <vector>
#include "AST_Node.hpp"
#include "../CST/Node.h"

using namespace std;

class AST {
  public:

    AST();

    void parse(NodePtr *Croot);




  private:
    AST_Node *root;


};

// give a vector of nodes that make up an expression in infix
// outputs a vector of these nodes in postfix order
vector<Node> inToPostFix (const vector<Node>& inFix);

#endif // ASSIGNMENT1_460_AST_HPP
