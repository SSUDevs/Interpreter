//
// Created by Luis carmona on 3/28/24.
//

#include "SymbolTablesLinkedList.h"


SymbolTablesLinkedList::SymbolTablesLinkedList(const NodePtr CST_root) {
    curCstNode = CST_root;
}

SymTblPtr SymbolTablesLinkedList::parse() {

    while (peekNextCstNode() != nullptr) {
        if (isDataType(nodeValue(peekNextCstNode()))) {
            declarationTable();
        }
        else if (nodeValue(peekNextCstNode()) == "function") {
            functionTable();
        }
        else if (nodeValue(peekNextCstNode()) == "procedure") {
            procedureTable();
        }
        // skip nodes until it's a node used for a symbol table
        else
            getNextCstNode();
    }

    return root;
}


// increments to next cstNode, also returning the curCSTNode.
// Note: only the leftChild or rightSib can have a node, not both
NodePtr SymbolTablesLinkedList::getNextCstNode() {

    if (curCstNode->rightSibling != nullptr) {
        curCstNode = curCstNode->rightSibling;
    }
    else if (curCstNode->leftChild != nullptr) {
        curCstNode = curCstNode->leftChild;
    }
    else {
        cerr << "Unexpected end of CST." << endl;
        exit(666);
    }

    return curCstNode;

}


// returns next valid node in CST
NodePtr SymbolTablesLinkedList::peekNextCstNode() {
    if (curCstNode->rightSibling != nullptr) {
        return curCstNode->rightSibling;
    }
    else if (curCstNode->leftChild != nullptr) {
        return curCstNode->leftChild;
    }

    return nullptr;
}

string SymbolTablesLinkedList::nodeValue(NodePtr node) {
    if (!node) {
        cerr << "Can't get value of a nullptr" << endl;
        exit (1111);
    }

    return node->Value().value();
}

// append a table to linked list of tables
void SymbolTablesLinkedList::addToSymTable(SymTblPtr s) {
    if (!root) {
        root = s;
    }
    else {
        lastTable->nextTable = s;
    }

    lastTable = s;
}

void SymbolTablesLinkedList::declarationTable() {

}

void SymbolTablesLinkedList::functionTable() {

}

void SymbolTablesLinkedList::procedureTable() {

}