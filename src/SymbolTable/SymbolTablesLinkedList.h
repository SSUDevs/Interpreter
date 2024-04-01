#ifndef ASSIGNMENT1_460_SYMBOLTABLESLINKEDLIST_H
#define ASSIGNMENT1_460_SYMBOLTABLESLINKEDLIST_H
#include "../CST/Node.h"
#include "../CST/Parser.h"
#include "SymbolTable.h"
#include <vector>e
using namespace std;

class SymbolTablesLinkedList {
  public:
    SymbolTablesLinkedList(const NodePtr CST_root);

    SymTblPtr parse();

    NodePtr getNextCstNode();
    NodePtr peekNextCstNode();

    string nodeValue(NodePtr node);

    void addToSymTable(SymTblPtr s);

    // functions for creating tables. specific to the types of table
    void declarationTable();
    void functionTable();
    void procedureTable();

    // Creating symbol tables for parameter lists for Procedures and Functions
    void parseParameters(const string &);

    private : NodePtr curCstNode;

    size_t current = 0;
    SymTblPtr root;
    SymTblPtr lastTable;
    int currentScope;
};

#endif // ASSIGNMENT1_460_SYMBOLTABLESLINKEDLIST_H
