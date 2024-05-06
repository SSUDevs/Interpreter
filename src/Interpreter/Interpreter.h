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
    NodePtr peekNext(NodePtr node);

    NodePtr findMain(const NodePtr &astroot, const SymTblPtr &symroot);
    void executeAssignment(NodePtr node);
    int evaluateExpression(NodePtr exprRoot, NodePtr endCase = nullptr, bool inAssignment = false);
    void updateSymbolTable(const string &name, int value, int index = 0);
    int getSymbolTableValue(const string &name, int index = 0);

    void executeIF();

    bool isOperand(Token t);
    bool isOperator(Token t);
    int applyOperator(Token::Type op, int left, int right, bool inAssignment = false);
    bool ParseSymbolTables(SymTblPtr root,const string &name,int value, int index);

    int getValue(string id, int elementNum = 0);

  private:
    SymTblPtr rootTable;
    NodePtr astRoot;


    NodePtr PC;

    string printF_buffer;

    stack<NodePtr> pc_stack;
    stack<NodePtr> arithmetic_stack;
};

#endif // INTERPRETER_H
