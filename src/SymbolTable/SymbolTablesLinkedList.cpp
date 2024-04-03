#include "SymbolTablesLinkedList.h"

SymbolTablesLinkedList::SymbolTablesLinkedList(const NodePtr CST_root)
    : curCstNode(CST_root), scopeCount(0), currentScope(0) {
    curCstNode = CST_root;
}

SymTblPtr SymbolTablesLinkedList::parse() {
    int braceCount = 0;
    currentScope = 0;

    parseRootNode();

    while (peekNextCstNode() != nullptr) {
        if (isDataType(nodeValue(peekNextCstNode()))) {
            declarationTable();
        } else if (nodeValue(peekNextCstNode()) == "function") {
            scopeCount++;
            currentScope = scopeCount;
            functionTable();
        } else if (nodeValue(peekNextCstNode()) == "procedure") {
            scopeCount++;
            currentScope = scopeCount;
            procedureTable();
        }
        // skip nodes until it's a node used for a symbol table
        else {
            if (nodeValue(peekNextCstNode()) == "{") {
                braceCount++;
            } else if (nodeValue(peekNextCstNode()) == "}") {
                braceCount--;
                if (braceCount == 0)
                    currentScope = 0;
            }
            getNextCstNode();
        }
    }
    return root;
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

string SymbolTablesLinkedList::nodeValue(NodePtr node) {
    if (!node) {
        cerr << "Can't get value of a nullptr" << endl;
        exit(1111);
    }

    return node->Value().value();
}

// append a table to linked list of tables
void SymbolTablesLinkedList::addToSymTable(SymTblPtr s) {
    if (!root) {
        root = s;
    } else {
        lastTable->nextTable = s;
    }

    lastTable = s;
}

void SymbolTablesLinkedList::declarationTable() {
    bool anotherDeclaration = false;
    string dataType;
    string repeatDataType;
    do {                          // For multi declaration on single-line
        if (anotherDeclaration) { // Inline declarations repreat datatype
            dataType = repeatDataType;
        } else {
            auto dataTypeNode = getNextCstNode();
            dataType = nodeValue(dataTypeNode);
        }
        anotherDeclaration = false;
        auto varNameNode = getNextCstNode();
        string varName = nodeValue(varNameNode);

        // Check for redeclarations of varaibles
        for (int i = 0; i < varaibleDeclared.size(); i++) {
            if (varaibleDeclared.at(i).first == varName) {
                if (varaibleDeclared.at(i).second == 0) {
                    std::cerr << "Error on line "
                              << varNameNode->Value().lineNum() << ": variable "
                              << nodeValue(varNameNode)
                              << " is already defined globally";
                    exit(60);
                }
                if (varaibleDeclared.at(i).second == currentScope) {
                    std::cerr << "Error on line "
                              << varNameNode->Value().lineNum() << ": variable "
                              << nodeValue(varNameNode)
                              << " is already defined locally";
                    exit(61);
                }
                if (currentScope == 0) {
                    std::cerr << "Error on line "
                              << varNameNode->Value().lineNum() << ": variable "
                              << nodeValue(varNameNode)
                              << " trying define global variable that is "
                                 "already defined";
                    exit(62);
                }
            }
        }
        varaibleDeclared.push_back(
            make_pair(nodeValue(varNameNode),
                      currentScope)); // Add the variable declaration

        bool isArray = false;
        int arraySize = 0;

        // Check if the variable is an array
        if (nodeValue(peekNextCstNode()) == "[") {
            getNextCstNode();                 // Skip '['
            auto sizeNode = getNextCstNode(); // Get the array size
            arraySize = std::stoi(nodeValue(sizeNode));
            getNextCstNode(); // Skip past ']'
            isArray = true;
        }

        // Create symbol table entry for the variable
        auto varEntry = std::make_shared<SymbolTable>();
        varEntry->_idName = varName;
        varEntry->_dataType = dataType;
        varEntry->_idtype = SymbolTable::IDType::datatype;
        varEntry->_isArray = isArray;
        varEntry->_arraySize = arraySize;
        varEntry->_scope = currentScope;

        addToSymTable(varEntry);
        if (nodeValue(peekNextCstNode()) == ",") {
            getNextCstNode(); // Skip comma and move to next declaration
            // Save dataType to repeat
            repeatDataType = dataType;
            anotherDeclaration = true;
        }
    } while (anotherDeclaration);
}

void SymbolTablesLinkedList::functionTable() {
    getNextCstNode();

    // Now at the return type of the function
    auto returnTypeNode = getNextCstNode();
    string returnType = nodeValue(returnTypeNode);

    // Now at the function name
    auto functionNameNode = getNextCstNode();
    string functionName = nodeValue(functionNameNode);

    for (int i = 0; i < funcProcNames.size(); i++) {
        if (funcProcNames.at(i) == functionName) {
            std::cerr << "Error: " << functionName
                      << " is already defined globally "
                      << nodeValue(peekNextCstNode()) << std::endl;
            exit(20);
        }
    }
    funcProcNames.push_back(functionName); // Add the function name declaration

    // Create symbol table entry for the function
    auto functionEntry = std::make_shared<SymbolTable>();
    functionEntry->_idName = functionName;
    functionEntry->_idtype = SymbolTable::IDType::function;
    functionEntry->_dataType = returnType;
    functionEntry->_scope = currentScope;
    functionEntry->_isArray = false;
    functionEntry->_arraySize = 0;

    addToSymTable(functionEntry);

    // Assume the '(' starts the parameter list
    getNextCstNode(); // Skip '(' to start processing parameters
    parseParameters(functionName);
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
    procedureEntry->_dataType = "void";    // Procedures have no return type
    procedureEntry->_scope = currentScope; // Add to scope for each procedure
    procedureEntry->_isArray = false;
    procedureEntry->_arraySize = 0;

    // Add procedure entry to the symbol table list
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
    getNextCstNode(); // Ends the procedure taking out the '{'.
}

void SymbolTablesLinkedList::parseParameters(
    const string &procedureOrFunctionName) {
    auto nextNode = peekNextCstNode();
    if (nodeValue(nextNode) == "void") {
        getNextCstNode(); // Skip 'void'
        return;
    }

    // Begin parsing parameters until the end of the parameter list.
    while (nodeValue(nextNode) != ")") {
        auto paramTypeNode =
            getNextCstNode(); // Get the data type of the parameter.
        auto paramNameNode = getNextCstNode(); // Get the name of the parameter.

        // Check for redeclarations of varaibles
        for (int i = 0; i < varaibleDeclared.size(); i++) {
            if (varaibleDeclared.at(i).first == nodeValue(paramNameNode)) {
                if (varaibleDeclared.at(i).second == 0)
                    std::cerr << "Error on line "
                              << paramNameNode->Value().lineNum()
                              << ": variable " << nodeValue(paramNameNode)
                              << " is already defined globally";
                exit(30);
                if (varaibleDeclared.at(i).second == currentScope) {
                    std::cerr << "Error on line "
                              << paramNameNode->Value().lineNum()
                              << ": variable " << nodeValue(paramNameNode)
                              << " is already defined locally";
                    exit(31);
                }
            }
        }
        varaibleDeclared.push_back(
            make_pair(nodeValue(paramNameNode),
                      currentScope)); // Add the variable declaration

        bool isArray = false;
        int arraySize = 0;

        // Check if the parameter is an array.
        if (nodeValue(peekNextCstNode()) == "[") {
            getNextCstNode(); // Skip '['
            auto arraySizeNode =
                getNextCstNode(); // Assuming the size is specified next.
            arraySize = std::stoi(
                nodeValue(arraySizeNode)); // Convert the size to an integer.
            getNextCstNode();              // Skip past ']'
            isArray = true;
        }

        // Create a new SymbolTable entry for this parameter.
        auto paramEntry = std::make_shared<SymbolTable>();
        paramEntry->_procOrFuncName = procedureOrFunctionName;
        paramEntry->_idName = nodeValue(paramNameNode);
        paramEntry->_dataType = nodeValue(paramTypeNode);
        paramEntry->_idtype = SymbolTable::IDType::parameterList;
        paramEntry->_isArray = isArray;
        paramEntry->_arraySize = arraySize;
        paramEntry->_scope = currentScope; // Parameters are at the same scope
                                           // level as the function/procedure

        addToSymTable(paramEntry);

        nextNode = peekNextCstNode(); // Peek at the next node to see if more
                                      // parameters exist.
        if (nodeValue(nextNode) == ",") {
            getNextCstNode(); // Skip the comma to move to the next parameter.
        }
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

            // Check for redeclarations of varaibles
            for (int i = 0; i < varaibleDeclared.size(); i++) {
                if (varaibleDeclared.at(i).first == varName) {
                    if (varaibleDeclared.at(i).second == 0) {
                        std::cerr << "Error on line "
                                  << varNameNode->Value().lineNum()
                                  << ": variable " << nodeValue(varNameNode)
                                  << " is already defined globally";
                        exit(20);
                    }
                    if (varaibleDeclared.at(i).second == currentScope) {
                        std::cerr << "Error on line "
                                  << varNameNode->Value().lineNum()
                                  << ": variable " << nodeValue(varNameNode)
                                  << " is already defined locally";
                        exit(21);
                    }
                    if (currentScope == 0) {
                        std::cerr << "Error on line "
                                  << varNameNode->Value().lineNum()
                                  << ": variable " << nodeValue(varNameNode)
                                  << " trying define global variable that is "
                                     "already defined";
                        exit(22);
                    }
                }
            }
            varaibleDeclared.push_back(
                make_pair(nodeValue(varNameNode),
                          currentScope)); // Add the variable declaration

            bool isArray = false;
            int arraySize = 0;

            // Check if the variable is an array
            if (nodeValue(peekNextCstNode()) == "[") {
                getNextCstNode();                 // Skip '['
                auto sizeNode = getNextCstNode(); // Get the array size
                arraySize = std::stoi(nodeValue(sizeNode));
                getNextCstNode(); // Skip past ']'
                isArray = true;
            }

            // Create symbol table entry for the variable
            auto varEntry = std::make_shared<SymbolTable>();
            varEntry->_idName = varName;
            varEntry->_dataType = dataType;
            varEntry->_idtype = SymbolTable::IDType::datatype;
            varEntry->_isArray = isArray;
            varEntry->_arraySize = arraySize;
            varEntry->_scope = currentScope;

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

        // Create symbol table entry for the function
        auto functionEntry = std::make_shared<SymbolTable>();
        functionEntry->_idName = functionName;
        functionEntry->_idtype = SymbolTable::IDType::function;
        functionEntry->_dataType = returnType;
        functionEntry->_scope = currentScope;
        functionEntry->_isArray = false;
        functionEntry->_arraySize = 0;

        addToSymTable(functionEntry);
        getNextCstNode();
        parseParameters(functionName);
    } else if (nodeValue(curCstNode) == "procedure") {
        scopeCount++;
        currentScope = scopeCount;

        // Now at procedure name
        auto procedureNameNode = getNextCstNode();
        string procedureName = nodeValue(procedureNameNode);

        // Create symbol table entry for the procedure
        auto procedureEntry = std::make_shared<SymbolTable>();
        procedureEntry->_idName = procedureName;
        procedureEntry->_idtype = SymbolTable::IDType::procedure;
        procedureEntry->_dataType = "void"; // Procedures have no return type
        procedureEntry->_scope =
            currentScope; // Add to scope for each procedure
        procedureEntry->_isArray = false;
        procedureEntry->_arraySize = 0;

        addToSymTable(procedureEntry);
        getNextCstNode();
        parseParameters(procedureName);
    }
}

void SymbolTablesLinkedList::printTables() {
    SymTblPtr current = root;

    while (current != nullptr) {
        cout << "IDENTIFIER_NAME: " << current->Name() << endl;
        cout << "IDENTIFIER_TYPE: " << current->idType() << endl;
        cout << "DATATYPE: " << current->dataType() << endl;
        cout << "DATATYPE_IS_ARRAY: " << current->isArray() << endl;
        cout << "DATATYPE_ARRAY_SIZE: " << current->arraySize() << endl;
        cout << "SCOPE: " << current->scope() << endl;
        cout << endl;

        current = current->nextTable;
    }
}