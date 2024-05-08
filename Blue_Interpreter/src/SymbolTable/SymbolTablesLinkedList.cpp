#include "SymbolTablesLinkedList.h"
#include "../ErrorHandler/ErrorHandler.h"

SymbolTablesLinkedList::SymbolTablesLinkedList(const NodePtr CST_root)
    : curCstNode(CST_root), scopeCount(0), currentScope(0) {
    curCstNode = CST_root;
}

// increments to next cstNode, also returning the curCSTNode.
// Note: only the leftChild or rightSib can have a node, not both
NodePtr SymbolTablesLinkedList::getNextCstNode() {
    if (curCstNode->rightSibling != nullptr) {
        curCstNode = curCstNode->rightSibling;
    } else if (curCstNode->leftChild != nullptr) {
        curCstNode = curCstNode->leftChild;
    } else {
        _globalErrorHandler.handle(27, 0);
    }

    return curCstNode;
}

// returns next valid node in CST
NodePtr SymbolTablesLinkedList::peekNextCstNode() {
    if (curCstNode->rightSibling != nullptr) {
        return curCstNode->rightSibling;
    } else if (curCstNode->leftChild != nullptr) {
        return curCstNode->leftChild;
    }

    return nullptr;
}

string SymbolTablesLinkedList::nodeValue(const NodePtr &node) const {
    if (!node) {
        string message = "Can't get value of a nullptr in the symbol table";
        _globalErrorHandler.handle(28, 0, message);
    }

    return node->Value().value();
}

// append a table to linked list of tables
void SymbolTablesLinkedList::addToSymTable(const SymTblPtr &s) {
    if (!root) {
        root = s;
    } else {
        lastTable->SetNextTable(s);
    }

    lastTable = s;
}

// Checks for redeclaration of a function or procedure name
void SymbolTablesLinkedList::checkFuncProcRedeclaration(const string &name,
                                                        const string &type) {
    for (const auto &existingName : funcProcNames) {
        if (existingName == name) {
            _globalErrorHandler.handle(31, 0, name, type);
        }
    }
    funcProcNames.push_back(name); // Add the name to the list
}

bool SymbolTablesLinkedList::checkVariableRedeclaration(const string &varName,
                                                        int scope,
                                                        int lineNumber) {
    for (const auto &var : variableDeclared) {
        if (var.first == varName) {
            // Existing variable is global (scope 0) and the same name.
            if (var.second == 0) {
                _globalErrorHandler.handle(29, lineNumber, varName);
            }
            // If the existing variable has the same scope as the current
            else if (var.second == scope) {
                _globalErrorHandler.handle(30, lineNumber, varName);
            }
            // If trying to define a global variable that's already defined
            if (scope == 0) {
                _globalErrorHandler.handle(31, lineNumber, varName);
            }
        }
    }
    // If no redeclaration is found, add the variable to the tracked
    variableDeclared.push_back(make_pair(varName, scope));
    return false; // No redeclaration found
}

pair<bool, int> SymbolTablesLinkedList::parseArrayDeclaration() {
    bool isArray = false;
    int arraySize = 0;
    auto nextNode = peekNextCstNode();
    if (nodeValue(nextNode) == "[") {
        getNextCstNode();                 // Skip '['
        auto sizeNode = getNextCstNode(); // Get the array size
        arraySize = stoi(nodeValue(sizeNode));
        getNextCstNode(); // Skip past ']'
        isArray = true;
    }
    return {isArray, arraySize};
}

SymTblPtr SymbolTablesLinkedList::parse() {
    int braceCount = 0;
    currentScope = 0;

    while (peekNextCstNode() != nullptr) {
        string currentNodeValue = nodeValue(curCstNode);
        if (isDataType(currentNodeValue)) {
            declarationTable();
        } else if (currentNodeValue == "function") {
            scopeCount++;
            currentScope = scopeCount;
            functionTable();
            currentScope = 0; // Reset scope to global after function parsing
        } else if (currentNodeValue == "procedure") {
            scopeCount++;
            currentScope = scopeCount;

            procedureTable();
            currentScope = 0; // Reset scope to global after procedure parsing
        } else {
            if (currentNodeValue == "{") {
                braceCount++;
            } else if (currentNodeValue == "}") {
                braceCount--;
                if (braceCount == 0) {
                    currentScope = 0; // Reset to global scope outside braces
                }
            }
            getNextCstNode(); // Move to the next node for unparsed or
                              // irrelevant tokens
        }
    }
    return root;
}

void SymbolTablesLinkedList::declarationTable() {
    bool anotherDeclaration = false;
    string dataType, repeatDataType;
    do {
        if (anotherDeclaration) {
            dataType = repeatDataType;
        } else if (currentScope == 0) {
            auto dataTypeNode = curCstNode;
            dataType = nodeValue(dataTypeNode);
        } else {
            auto dataTypeNode = getNextCstNode();
            dataType = nodeValue(dataTypeNode);
        }
        anotherDeclaration = false;
        auto varNameNode = getNextCstNode();
        string varName = nodeValue(varNameNode);

        // If no error then it is added to the variableDeclared vector
        if (checkVariableRedeclaration(varName, currentScope,
                                       varNameNode->Value().lineNum())) {
            continue;
        }
        auto [isArray, arraySize] = parseArrayDeclaration();

        // Updated symbol table entry creation
        auto varEntry = make_shared<SymbolTable>(
            varName, dataType, SymbolTable::IDType::datatype, currentScope,
            isArray, arraySize);
        addToSymTable(varEntry);

        if (nodeValue(peekNextCstNode()) == ",") {
            getNextCstNode();          // Skip comma for next declaration
            repeatDataType = dataType; // Next iteration if another declaration
            anotherDeclaration = true;
        }
    } while (anotherDeclaration);
}

void SymbolTablesLinkedList::functionTable() {
    auto returnTypeNode = getNextCstNode();
    string returnType = nodeValue(returnTypeNode);

    auto functionNameNode = getNextCstNode();
    string functionName = nodeValue(functionNameNode);

    // Checks for redeclaration and add sthe name to the list if not already
    // present
    checkFuncProcRedeclaration(functionName, "function");

    funcProcNames.push_back(functionName); // Add the function name declaration

    auto functionEntry = make_shared<SymbolTable>(
        functionName, returnType, SymbolTable::IDType::function, currentScope);
    addToSymTable(functionEntry);

    // Assume the '(' starts the parameter list
    getNextCstNode(); // Skip '(' to start processing parameters
    parseParameters(functionName);

    getNextCstNode(); // Skip past ')' marking the end of the parameter list.
    // Check the '{' that starts the procedure body.
    if (nodeValue(peekNextCstNode()) == "{") {
        getNextCstNode(); // Move past '{' to start processing the body
    } else {
        int lineNumber = peekNextCstNode()->Value().lineNum();
        string name = nodeValue(peekNextCstNode());
        _globalErrorHandler.handle(6, lineNumber, name);
    }
    while (nodeValue(peekNextCstNode()) !=
           "}") { // Check fot the '}' that marks the end of the procedure body.
        auto currentNodeValue = nodeValue(peekNextCstNode());
        if (isDataType(currentNodeValue)) { // Check if the next node indicates
                                            // a data type, i.e. a declaration.
            declarationTable();             // Process a declaration.
        } else {
            getNextCstNode(); // Skip nodes not relevant for the symbol table.
        }
    }
}

void SymbolTablesLinkedList::procedureTable() {
    auto procedureNameNode = getNextCstNode();
    string procedureName = nodeValue(procedureNameNode);

    // Checks for redeclaration and add sthe name to the list if not already
    // present
    checkFuncProcRedeclaration(procedureName, "procedure");

    auto procedureEntry = make_shared<SymbolTable>(
        procedureName, "void", SymbolTable::IDType::procedure, currentScope);

    addToSymTable(procedureEntry);

    // Check the '(' that starts the procedure params.
    if (nodeValue(peekNextCstNode()) == "(") {
        getNextCstNode(); // Move past '(' to start processing the params
    } else {
        int lineNumber = peekNextCstNode()->Value().lineNum();
        string name = nodeValue(peekNextCstNode());
        _globalErrorHandler.handle(12, lineNumber, name);
        return;
    }
    // Parse parameters creating its own symbol table
    parseParameters(procedureName);

    getNextCstNode(); // Skip past ')' marking the end of the parameter list.

    // Check the '{' that starts the procedure body.
    if (nodeValue(peekNextCstNode()) == "{") {
        getNextCstNode(); // Move past '{' to start processing the body
    } else {
        int lineNumber = peekNextCstNode()->Value().lineNum();
        string name = nodeValue(peekNextCstNode());
        _globalErrorHandler.handle(6, lineNumber, name);
    }
    while (nodeValue(peekNextCstNode()) !=
           "}") { // Check fot the '}' that marks the end of the procedure body.
        auto currentNodeValue = nodeValue(peekNextCstNode());
        if (isDataType(currentNodeValue)) { // Check if the next node indicates
                                            // a data type, i.e. a declaration.
            declarationTable();             // Process a declaration.
        } else {
            getNextCstNode(); // Skip nodes not relevant for the symbol table.
        }
    }
}

void SymbolTablesLinkedList::parseParameters(const string &procOrFuncName) {
    auto nextNode = peekNextCstNode();
    if (nodeValue(nextNode) == "void") {
        getNextCstNode(); // Skip 'void'
        return;
    }
    while (nodeValue(peekNextCstNode()) != ")") {
        auto paramTypeNode = getNextCstNode();
        string paramType = nodeValue(paramTypeNode);

        auto paramNameNode = getNextCstNode();
        string paramName = nodeValue(paramNameNode);

        // If no error then it is added to the variableDeclared vector
        if (checkVariableRedeclaration(paramName, currentScope,
                                       paramNameNode->Value().lineNum())) {
            continue;
        }
        auto [isArray, arraySize] = parseArrayDeclaration();

        auto paramEntry = make_shared<SymbolTable>(
            paramName, paramType, SymbolTable::IDType::parameterList,
            currentScope, isArray, arraySize, procOrFuncName);

        addToSymTable(paramEntry);

        if (nodeValue(peekNextCstNode()) == ",")
            getNextCstNode(); // Skip comma for multiple parameters
    }
}

void SymbolTablesLinkedList::printTables() {
    SymTblPtr current = root;

    while (current != nullptr) {
        cout << "IDENTIFIER_NAME: " << current->GetName() << endl;
        cout << "IDENTIFIER_TYPE: " << current->GetStringIdType() << endl;
        cout << "DATATYPE: " << current->GetDataType() << endl;
        cout << "DATATYPE_IS_ARRAY: " << current->GetIsArray() << endl;
        cout << "DATATYPE_ARRAY_SIZE: " << current->GetArraySize() << endl;
        cout << "SCOPE: " << current->GetScope() << endl;
        cout << endl;
        current = current->GetNextTable();
    }
}