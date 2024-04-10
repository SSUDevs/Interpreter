#ifndef SYMBOLTABLESLINKEDLIST_H
#define SYMBOLTABLESLINKEDLIST_H

#include "../CST/Node.h"
#include "../CST/Parser.h"
#include "SymbolTable.h"
#include <utility>
#include <vector>

using std::make_shared;
using std::pair;
using std::shared_ptr;
using std::vector;

class SymbolTablesLinkedList {
  public:
    SymbolTablesLinkedList(const NodePtr CST_root);

    SymTblPtr parse();
    void parseRootNode();

    NodePtr getNextCstNode();
    NodePtr peekNextCstNode();

    string nodeValue(const NodePtr &node) const;

    void addToSymTable(const SymTblPtr &s);

    // functions for creating tables. specific to the types of table
    void declarationTable();
    void functionTable();
    void procedureTable();
    void parseParameters(const string &procOrFuncName);

    // Helper methods for error handling and declaration checks
    void reportError(const string &message, int lineNumber,
                     int errorCode) const;
    void checkFuncProcRedeclaration(const string &name, const string &type);
  
    bool checkVariableRedeclaration(const string &varName, int scope,
                                    int lineNumber);
    pair<bool, int> parseArrayDeclaration();

    // Creating symbol tables for parameter lists for Procedures and Functions

    void printTables();

  private:
    NodePtr curCstNode;
    SymTblPtr root, lastTable;
    int currentScope, scopeCount;

    // Store all the defined variables
    vector<pair<string, int>> variableDeclared;

    // Store function/procedure names to check availability
    vector<string> funcProcNames;
};

#endif // SYMBOLTABLESLINKEDLIST_H
