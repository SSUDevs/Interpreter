#include "SymbolTablesLinkedList.h"

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
        cerr << "Unexpected end of CST." << endl;
        exit(666);
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
        cerr << "Can't get value of a nullptr" << endl;
        exit(1111);
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

void SymbolTablesLinkedList::reportError(const string &message, int lineNumber,
                                         int errorCode) const {
    cerr << "Error on line " << lineNumber << ": " << message << endl;
    exit(errorCode);
}

bool SymbolTablesLinkedList::checkVariableRedeclaration(const string &varName,
                                                        int scope,
                                                        int lineNumber) {
    for (const auto &var : variableDeclared) {
        if (var.first == varName) {
            // If the existing variable is global (scope 0) and we're trying to
            // declare another variable with the same name.
            if (var.second == 0) {
                cerr << "Error on line " << lineNumber << ": variable \""
                     << varName << "\" is already defined globally!" << endl;
                exit(
                    60); // Use the specific error code for global redeclaration
            }
            // If the existing variable has the same scope as the current
            // declaration, it's a local redeclaration error.
            else if (var.second == scope) {
                cerr << "Error on line " << lineNumber << ": variable \""
                     << varName
                     << "\" is already defined locally in the same scope!!"
                     << endl;
                exit(61); // Use the specific error code for local scope
                          // redeclaration
            }
            // If trying to define a global variable that's already defined
            // elsewhere.
            if (scope == 0) {
                cerr << "Error on line " << lineNumber << ": variable \""
                     << varName
                     << "\" trying to define a global variable that is already "
                        "defined elsewhere!!!"
                     << endl;
                exit(62); // Use the specific error code for attempting to
                          // globally redefine a variable
            }
        }
    }
    // If no redeclaration is found, add the variable to the tracked
    // declarations and return false to indicate no errors.
    variableDeclared.push_back(make_pair(varName, scope));
    cout << "variable defined: " << varName << " with scope: " << scope << endl;
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

    parseRootNode();

    while (peekNextCstNode() != nullptr) {
        string currentNodeValue = nodeValue(peekNextCstNode());
        if (isDataType(currentNodeValue)) {
            declarationTable();
        } else if (currentNodeValue == "function") {
            scopeCount++;
            currentScope = scopeCount;

            cout << "Function found with scope: " << currentScope << endl;

            functionTable();
            currentScope = 0; // Reset scope to global after function parsing
        } else if (currentNodeValue == "procedure") {
            scopeCount++;
            currentScope = scopeCount;

            cout << "Procedure found with scope: " << currentScope << endl;

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
    getNextCstNode(); // Skip 'function' keyword
    auto returnTypeNode = getNextCstNode();
    string returnType = nodeValue(returnTypeNode);

    cout << "Entering function with return type: " << returnType
         << "and scope: " << currentScope << endl;

    auto functionNameNode = getNextCstNode();
    string functionName = nodeValue(functionNameNode);

    // Check for function redeclaration
    for (int i = 0; i < funcProcNames.size(); i++) {
        if (funcProcNames.at(i) == functionName) {
            std::cerr << "Error: \"" << functionName
                      << "\" is already defined globally "
                      << nodeValue(peekNextCstNode()) << std::endl;
            exit(20);
        }
    }
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
        std::cerr << "Expected '{' at the start of the procedure body. Found: "
                  << nodeValue(peekNextCstNode()) << std::endl;
        return;
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
    getNextCstNode(); // Skip 'procedure' keyword

    auto procedureNameNode = getNextCstNode();
    string procedureName = nodeValue(procedureNameNode);

    // Check for procedure redeclaration
    for (int i = 0; i < funcProcNames.size(); i++) {
        if (funcProcNames.at(i) == procedureName) {
            std::cerr << "Error: \"" << procedureName
                      << "\" is already defined globally "
                      << nodeValue(peekNextCstNode()) << std::endl;
            exit(20);
        }
    }
    funcProcNames.push_back(
        procedureName); // Add procedure name to track redeclarations

    auto procedureEntry = make_shared<SymbolTable>(
        procedureName, "void", SymbolTable::IDType::procedure, currentScope);

    addToSymTable(procedureEntry);

    // Check the '(' that starts the procedure params.
    if (nodeValue(peekNextCstNode()) == "(") {
        getNextCstNode(); // Move past '(' to start processing the params
    } else {
        std::cerr << "Expected '(' at the start of the procedure body. Found: "
                  << nodeValue(peekNextCstNode()) << std::endl;
        return;
    }
    // Parse parameters creating its own symbol table
    parseParameters(procedureName);

    // Parsing of the procedure body
    getNextCstNode(); // Skip past ')' marking the end of the parameter list.

    // Check the '{' that starts the procedure body.
    if (nodeValue(peekNextCstNode()) == "{") {
        getNextCstNode(); // Move past '{' to start processing the body
    } else {
        std::cerr << "Expected '{' at the start of the procedure body. Found: "
                  << nodeValue(peekNextCstNode()) << std::endl;
        return;
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
            paramName, paramType,
            SymbolTable::IDType::parameterList, currentScope, isArray,
            arraySize, procOrFuncName);

        addToSymTable(paramEntry);

        if (nodeValue(peekNextCstNode()) == ",")
            getNextCstNode(); // Skip comma for multiple parameters
    }
}

void SymbolTablesLinkedList::parseRootNode() {
    auto currNode = curCstNode;
    bool anotherDeclaration = false;
    if (isDataType(nodeValue(currNode))) {
        bool anotherDeclaration = false;
        string dataType;
        string repeatDataType;
        do {                          // For multi declaration on single-line
            if (anotherDeclaration) { // Inline declarations repreat datatype
                dataType = repeatDataType;
            } else {
                dataType = nodeValue(currNode);
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

            // Create symbol table entry for the variable
            auto varEntry = make_shared<SymbolTable>(
                varName, dataType, SymbolTable::IDType::datatype, currentScope,
                isArray, arraySize);

            addToSymTable(varEntry);

            if (nodeValue(peekNextCstNode()) == ",") {
                getNextCstNode(); // Skip comma and move to next declaration
                // Save dataType to repeat
                repeatDataType = dataType;
                anotherDeclaration = true;
            }

        } while (anotherDeclaration);

    } else if (nodeValue(curCstNode) == "function") {
        scopeCount++;
        currentScope = scopeCount;

        // Now at the return type of the function
        auto returnTypeNode = getNextCstNode();
        string returnType = nodeValue(returnTypeNode);

        // Now at the function name
        auto functionNameNode = getNextCstNode();
        string functionName = nodeValue(functionNameNode);

        // Check for procedure redeclaration
        for (int i = 0; i < funcProcNames.size(); i++) {
            if (funcProcNames.at(i) == functionName) {
                std::cerr << "Error: \"" << functionName
                          << "\" is already defined globally "
                          << nodeValue(peekNextCstNode()) << std::endl;
                exit(20);
            }
        }
        funcProcNames.push_back(
            functionName); // Add procedure name to track redeclarations

        // Create symbol table entry for the function
        auto functionEntry = make_shared<SymbolTable>(
            functionName, returnType, SymbolTable::IDType::function,
            currentScope, false, 0);

        addToSymTable(functionEntry);
        getNextCstNode();
        parseParameters(functionName);
    } else if (nodeValue(curCstNode) == "procedure") {
        scopeCount++;
        currentScope = scopeCount;

        // Now at procedure name
        auto procedureNameNode = getNextCstNode();
        string procedureName = nodeValue(procedureNameNode);

        // Check for procedure redeclaration
        for (int i = 0; i < funcProcNames.size(); i++) {
            if (funcProcNames.at(i) == procedureName) {
                std::cerr << "Error: \"" << procedureName
                          << "\" is already defined globally "
                          << nodeValue(peekNextCstNode()) << std::endl;
                exit(20);
            }
        }
        funcProcNames.push_back(
            procedureName); // Add procedure name to track redeclarations

        // Create symbol table entry for the procedure
        auto procedureEntry = make_shared<SymbolTable>(
            procedureName, "void", SymbolTable::IDType::procedure, currentScope,
            false, 0);

        addToSymTable(procedureEntry);
        getNextCstNode();
        parseParameters(procedureName);
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