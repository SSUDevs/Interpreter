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
    // Move past "procedure" keyword
    getNextCstNode();
    
    // Now at procedure name
    auto procedureNameNode = getNextCstNode(); 
    string procedureName = nodeValue(procedureNameNode);

    // Create symbol table entry for the procedure
    auto procedureEntry = std::make_shared<SymbolTable>();
    procedureEntry->_idName = procedureName;
    procedureEntry->_idtype = SymbolTable::IDType::procedure;
    procedureEntry->_dataType = "void"; // Procedures have no return type
    procedureEntry->_scope = current++; // Add to scope for each procedure
    procedureEntry->_isArray = false;
    procedureEntry->_arraySize = 0;

    // Add procedure entry to the symbol table list
    addToSymTable(procedureEntry); 

    // Check the '(' that starts the procedure params.
    if (nodeValue(peekNextCstNode()) == "(") {
        getNextCstNode(); // Move past '(' to start processing the params
    } else {
        std::cerr << "Expected '(' at the start of the procedure body. Found: " << nodeValue(peekNextCstNode()) << std::endl;
        return;
    }
    // Parse parameters creating its own symbol table
    parseParameters(procedureName); // Also Removes the ending ')'
    
    // Check the '{' that starts the procedure body.
    if (nodeValue(peekNextCstNode()) == "{") {
        getNextCstNode(); // Move past '{' to start processing the body
    } else {
        std::cerr << "Expected '{' at the start of the procedure body. Found: " << nodeValue(peekNextCstNode()) << std::endl;
        return;
    }
    while (nodeValue(peekNextCstNode()) != "}") { // Check fot the '}' that marks the end of the procedure body.
        auto currentNodeValue = nodeValue(peekNextCstNode());
        if (isDataType(currentNodeValue)) { // Check if the next node indicates a data type, i.e. a declaration.
            declarationTable(); // Process a declaration. 
        } else {
            getNextCstNode(); // Skip nodes not relevant for the symbol table.
        }
    }
    getNextCstNode(); // Ends the procedure taking out the '{'.
}

void SymbolTablesLinkedList::parseParameters(const string& procedureOrFunctionName) {
    auto nextNode = peekNextCstNode(); 
    if (nodeValue(nextNode) == "void") {
        getNextCstNode(); // Skip 'void'
        return;
    }

    // Begin parsing parameters until the end of the parameter list.
    while (nodeValue(nextNode) != ")") {
        auto paramTypeNode = getNextCstNode(); // Get the data type of the parameter.
        auto paramNameNode = getNextCstNode(); // Get the name of the parameter.
        bool isArray = false;
        int arraySize = 0;

        // Check if the parameter is an array.
        if (nodeValue(peekNextCstNode()) == "[") {
            getNextCstNode(); // Skip '['
            auto arraySizeNode = getNextCstNode(); // Assuming the size is specified next.
            arraySize = std::stoi(nodeValue(arraySizeNode)); // Convert the size to an integer.
            getNextCstNode(); // Skip past ']'
            isArray = true;
        }

        // Create a new SymbolTable entry for this parameter.
        auto paramEntry = std::make_shared<SymbolTable>();
        paramEntry->_idName = nodeValue(paramNameNode);
        paramEntry->_dataType = nodeValue(paramTypeNode);
        paramEntry->_idtype = SymbolTable::IDType::datatype; // Using datatype for parameters.
        paramEntry->_isArray = isArray;
        paramEntry->_arraySize = arraySize;
        paramEntry->_scope = currentScope; // Parameters are at the same scope level as the function/procedure

        addToSymTable(paramEntry);

        nextNode = peekNextCstNode(); // Peek at the next node to see if more parameters exist.
        if (nodeValue(nextNode) == ",") {
            getNextCstNode(); // Skip the comma to move to the next parameter.
        }
    }

    getNextCstNode(); // Skip past ')' marking the end of the parameter list.
}
