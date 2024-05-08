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

    void executeAssignment(NodePtr node);
    int evaluateExpression(NodePtr exprRoot, NodePtr endCase = nullptr, bool inAssignment = false);

    void updateSymbolTable(const string &name, int value, int scope, int index = 0 );
    int getSymbolTableValue(const string &name, int scope, int index = 0);
    SymTblPtr getSymbolTable(const string &name, int scope, bool isProOrFun = false);
    SymTblPtr getSTofFuncOrProcByScope(const int scope);
    SymTblPtr getNthParamOfFuntOrProc (const string name, int num, int scope);

    NodePtr findFunctOrProcStart (const string name);
    int findNumParamsOfFunctOrProc(const string name);

    void executeIF();

    bool isOperand(Token t);
    bool isOperator(Token t);
    int applyOperator(Token::Type op, int left, int right, bool inAssignment = false);
    bool UpdateTable(SymTblPtr root,const string &name,int value, int index, int scope);
    void executePrintF(NodePtr Node);
    void executeFunctionOrProcedureCall();

    void executeFor();
    void executeWhile();

    void executeDeclaration(string variable, int scope = -1);
    void executeReturn ();
    void executeCall();

  private:
    SymTblPtr rootTable;
    NodePtr astRoot;

    stack<int> scopeStack;



    NodePtr PC;

    string printF_buffer;

    stack<NodePtr> pc_stack;
    stack<NodePtr> arithmetic_stack;
};

#endif // INTERPRETER_H
