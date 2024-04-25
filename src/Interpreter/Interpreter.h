//
// Created by Evan on 4/24/2024.
//
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stack>
#include "../Node/Node.h"
#include "../SymbolTable/SymbolTablesLinkedList.h"
#include "../AST/ASTParser.h"

using namespace std;

class Interpreter {
  public:
    Interpreter (const NodePtr &astRoot, const SymTblPtr &symTblRoot); // not implemented


    NodePtr iteratePC();    // not implemented
    NodePtr peekNext();     // not implemented

  private:

    SymTblPtr rootTable;
    NodePtr astRoot;

    NodePtr PC;
    stack<NodePtr> pc_stack;
    stack<NodePtr> arithmetic_stack;

};

#endif // INTERPRETER_H
