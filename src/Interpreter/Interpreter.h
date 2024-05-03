//
// Created by Evan on 4/24/2024.
//
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "../AST/ASTParser.h"
#include "../Node/Node.h"
#include "../SymbolTable/SymbolTablesLinkedList.h"
#include <stack>

using namespace std;

class Interpreter {
  public:
    Interpreter(const NodePtr &astRoot, const SymTblPtr &symTblRoot);

    NodePtr iteratePC();
    NodePtr peekNext();

    NodePtr findMain(const NodePtr &astroot, const SymTblPtr &symroot);
    void executeAssignment(NodePtr node);
    int evaluateExpression(NodePtr exprRoot);
    void updateSymbolTable(const string &name, int value);

    bool isOperand();
    bool isOperator(Token t);
    int applyOperator(Token::Type op, int left, int right);


  private:
    SymTblPtr rootTable;
    NodePtr astRoot;


    NodePtr PC;

    string printF_buffer;

    stack<NodePtr> pc_stack;
    stack<NodePtr> arithmetic_stack;
};

#endif // INTERPRETER_H
