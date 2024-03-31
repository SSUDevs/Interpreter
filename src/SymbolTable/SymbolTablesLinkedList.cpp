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
    // The current node should be the "procedure" identifier when entering this function
    auto procedureNameNode = getNextCstNode(); // Move to the procedure name node.
    string procedureName = nodeValue(procedureNameNode);

    // Create a new symbol table entry for the procedure.
    auto procedureEntry = make_shared<SymbolTable>();
    procedureEntry->_idName = procedureName;
    procedureEntry->_idtype = SymbolTable::IDType::procedure;
    procedureEntry->_dataType = "NOT APPLICABLE"; // Procedures don't have a return type.
    procedureEntry->_scope = currentScope++; // Increment current scope for the procedure body.
    addToSymTable(procedureEntry);

    // Move to the parameter list or the procedure body if there are no parameters.
    auto paramOrBodyNode = getNextCstNode(); // This will be the first parameter or the body if no parameters
    
    // Check if the node represents a parameter list start or the procedure body.
    if (nodeValue(paramOrBodyNode) == "parameterListStart") {
        auto paramNode = getNextCstNode(); // Move to the first parameter data type node.

        while (nodeValue(paramNode) != "parameterListEnd") { // Check for end of parameter list marker.
            string paramDataType = nodeValue(paramNode);
            auto paramNameNode = getNextCstNode(); // Move to the parameter name node.
            string paramName = nodeValue(paramNameNode);

            // Create a new symbol table entry for the parameter.
            auto paramEntry = make_shared<SymbolTable>();
            paramEntry->_idName = paramName;
            paramEntry->_dataType = paramDataType;
            paramEntry->_idtype = SymbolTable::IDType::datatype;
            paramEntry->_scope = currentScope; // The parameter is in the same scope as the procedure body.
            addToSymTable(paramEntry);

            paramNode = getNextCstNode(); // Move to the next parameter or the end of the parameter list.
        }

        // Move past the "parameterListEnd" marker to the procedure body.
        paramOrBodyNode = getNextCstNode();
    }

    // At this point, paramOrBodyNode should point to the start of the procedure body.
    // Further processing of the procedure body would continue from here, we can reuse
    // the declarationTable() method for any local variable declarations or similar logic
    // for handling statements within the procedure.

    // Reset or decrement the current scope after exiting the procedure body.
    currentScope--;
}