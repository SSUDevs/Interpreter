
#include "Parser.h"
#include <iostream>
using namespace std;
// Use make_shared to dynamically allocate Node instances. 
// When a new node is created, it's managed by a shared_ptr.

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

NodePtr Parser::parse() {

    while (current < tokens.size()) {

        Token t = getToken();

        if (t.type() == Token::Type::Identifier) {
            string tokenValue = t.value();

            if (isDataType(tokenValue)) {
                parseDeclaration();
            }   
            else if (tokenValue == "procedure") {
                parseProcedure();
            }  
            else if (tokenValue == "function") {
                // parseFunction();
            }
            else { // error, global scope can only contain global variable declarations, procedures, and functions
                cerr << "Invalid syntax in global scope at line " << t.lineNum() << endl;
                exit(1);
            }
        }
    }
       
    return root;
}

Token Parser::getToken() {
    if (current < tokens.size()) {
        return tokens[current++]; // Corrected to avoid returning a reference
    } else {
        throw std::runtime_error("Unexpected end of input");
    }
}

void Parser::addToCST(NodePtr node, InsertionMode mode) {
    if (!root) {
        root = node;
    }
    else {
        if (mode == LeftChild)
            lastNode->leftChild = node;
        else
            lastNode->rightSibling = node;
    }
    lastNode = node;
}

NodePtr Parser::createNodePtr(const Token& token) {
    // Create a Node object with the provided Token
    NodePtr nodePtr = std::make_shared<Node>(token);
    return nodePtr;
}

bool Parser::match(Token::Type type, Token t) {
    if (t.type() == type) {
        return true;
    }
    return false;
}

void Parser::parseDeclaration() {

    Token currToken = tokens[current];



    if (match(Token::Type::Identifier, currToken) && isDataType(currToken.value())) {
        addToCST(createNodePtr(currToken),
                 LeftChild); // add data type id to CST


    if (match(Token::Type::Identifier, currToken) && isDataType(currToken.value())) {
        addToCST(createNodePtr(currToken),
                 LeftChild); // add data type id to CST

        parseIDENTIFIER_AND_IDENTIFIER_ARRAY_LIST(); // add list of identifiers

        // semicolon check and add
        parseIDENTIFIER_AND_IDENTIFIER_ARRAY_LIST(); // add list of identifiers

        // semicolon check and add
        currToken = getToken();
        if (!match(Token::Type::Semicolon, currToken)) { // ERROR reserved name
            cerr << "Syntax error on line " << currToken.lineNum()
                 << ": missing ';'" << endl;
            exit(1);
        }
        addToCST(createNodePtr(currToken), RightSibling); // add name id to CST
    }
}

void Parser::parseIDENTIFIER_AND_IDENTIFIER_ARRAY_LIST() {

    while (!match(Token::Type::Semicolon, tokens[current])){
        parseIDENTIFIER_ARRAY_LIST();
        parseIDENTIFIER_LIST();
    }
}

void Parser::parseIDENTIFIER_ARRAY_LIST() {
    Token currToken = getToken();
    Token nextToken = getToken();
    bool foundEnd = false;

    while (match(Token::Type::Identifier, currToken) && !foundEnd) {
        if (isReserved(currToken.value())) {    // check reserved
        if (!match(Token::Type::Semicolon, currToken)) { // ERROR reserved name
            cerr << "Syntax error on line " << currToken.lineNum()
                 << ": missing ';'" << endl;
            exit(1);
        }
        addToCST(createNodePtr(currToken), RightSibling); // add name id to CST
    }
}

void Parser::parseIDENTIFIER_AND_IDENTIFIER_ARRAY_LIST() {

    while (!match(Token::Type::Semicolon, tokens[current])){
        parseIDENTIFIER_ARRAY_LIST();
        parseIDENTIFIER_LIST();
    }
}

void Parser::parseIDENTIFIER_ARRAY_LIST() {
    Token currToken = getToken();
    Token nextToken = getToken();
    bool foundEnd = false;

    while (match(Token::Type::Identifier, currToken) && !foundEnd) {
        if (isReserved(currToken.value())) {    // check reserved
            cerr << "Syntax error on line " << currToken.lineNum() << ": reserved word \""
                 << currToken.value() << "\" cannot be used for a variable name." << endl;
                 << currToken.value() << "\" cannot be used for a variable name." << endl;
            exit(1);
        }

        if (match(Token::Type::LBracket, nextToken)){
            addToCST(createNodePtr((currToken)), RightSibling); // add array name
            addToCST(createNodePtr((nextToken)), RightSibling); // add left bracket

            Token num = getToken();
            if (isReserved(num.value())) {    // check reserved
                cerr << "Syntax error on line " << num.lineNum() << ": reserved word \""
                     << num.value() << "\" cannot be used for a variable name." << endl;
                exit(1);
            }
            if (stoi(num.value()) <= 0 && !match(Token::Type::Identifier, num)) {     // ERROR negative array size
                cerr << "Syntax error on line " << num.lineNum() << ": array declaration size must be a positive integer." << endl;
                exit(1);
            }
            addToCST(createNodePtr((num)), RightSibling); // add num/variable name

            nextToken = getToken(); // get right bracket
            if (!match(Token::Type::RBracket, nextToken)) {     // ERROR negative array size
                cerr << "Syntax error on line " << nextToken.lineNum() << ": Incomplete bracket." << endl;
                exit(1);
            }
            addToCST(createNodePtr((nextToken)), RightSibling); // add right bracket

            nextToken = getToken();
            if (match(Token::Type::Comma, nextToken)) {
                addToCST(createNodePtr((nextToken)), RightSibling); // add comma
                currToken = getToken();
                nextToken = getToken();
            } else {
                foundEnd = true;
                current--;
            }
        }
        else
            current-=2;
    }


}

void Parser::parseIDENTIFIER_LIST() {
    Token currToken = getToken();
    Token nextToken = getToken();

    bool foundEnd = false;

    while (match(Token::Type::Identifier, currToken) && !foundEnd) {
        if (isReserved(currToken.value())) {
            cerr << "Syntax error on line " << currToken.lineNum() << ": reserved word \""
                 << currToken.value() << "\" cannot be used for a variable name." << endl;

        if (match(Token::Type::LBracket, nextToken)){
            addToCST(createNodePtr((currToken)), RightSibling); // add array name
            addToCST(createNodePtr((nextToken)), RightSibling); // add left bracket

            Token num = getToken();
            if (isReserved(num.value())) {    // check reserved
                cerr << "Syntax error on line " << num.lineNum() << ": reserved word \""
                     << num.value() << "\" cannot be used for a variable name." << endl;
                exit(1);
            }
            if (stoi(num.value()) <= 0 && !match(Token::Type::Identifier, num)) {     // ERROR negative array size
                cerr << "Syntax error on line " << num.lineNum() << ": array declaration size must be a positive integer." << endl;
                exit(1);
            }
            addToCST(createNodePtr((num)), RightSibling); // add num/variable name

            nextToken = getToken(); // get right bracket
            if (!match(Token::Type::RBracket, nextToken)) {     // ERROR negative array size
                cerr << "Syntax error on line " << nextToken.lineNum() << ": Incomplete bracket." << endl;
                exit(1);
            }
            addToCST(createNodePtr((nextToken)), RightSibling); // add right bracket

            nextToken = getToken();
            if (match(Token::Type::Comma, nextToken)) {
                addToCST(createNodePtr((nextToken)), RightSibling); // add comma
                currToken = getToken();
                nextToken = getToken();
            } else {
                foundEnd = true;
                current--;
            }
        }
        else
            current-=2;
    }


}

void Parser::parseIDENTIFIER_LIST() {
    Token currToken = getToken();
    Token nextToken = getToken();

    bool foundEnd = false;

    while (match(Token::Type::Identifier, currToken) && !foundEnd) {
        if (isReserved(currToken.value())) {
            cerr << "Syntax error on line " << currToken.lineNum() << ": reserved word \""
                 << currToken.value() << "\" cannot be used for a variable name." << endl;
            exit(1);
        }

        // next token not bracket
        if (!match(Token::Type::LBracket, nextToken)) {
            addToCST(createNodePtr((currToken)), RightSibling); // add variable name
            if (match(Token::Type::Comma, nextToken)) {
                addToCST(createNodePtr((nextToken)), RightSibling); // add comma
                currToken = getToken();
                nextToken = getToken();
            } else {
                foundEnd = true;
                current--;
            }
        }
        else
            current-=2;
    }
}

// NOTES:
// <PROCEDURE_DECLARATION> ::= procedure <IDENTIFIER> <L_PAREN>
// <PARAMETER_LIST> <R_PAREN> < L_BRACE> <COMPOUND_STATEMENT> <R_BRACE>
// | procedure <IDENTIFIER> <L_PAREN> void <R_PAREN> < L_BRACE>
// <COMPOUND_STATEMENT> <R_BRACE>

// Parses a procedure declaration, including its name, parameter list, and body.
void Parser::parseProcedure() {
    // Get and validate the procedure identifier token.
    Token identifier = getToken();
    if (identifier.type() != Token::Type::Identifier) {
        cerr << "Syntax error: Expected an identifier for the procedure name, found '"
             << identifier.value() << "' at line " << identifier.lineNum() << "." << endl;
        exit(1);
    }
    
    // Create a procedure declaration node with the identifier and add it to the CST.
    NodePtr procedureNode = createNodePtr(identifier);
    addToCST(procedureNode, LeftChild);
    
    // Expect and validate the left parenthesis '(' token.
    NodePtr lParenNode = expectToken(Token::Type::LParen, "Expected '(' after procedure name.");
    addToCST(lParenNode, RightSibling);
    
    // Peek at the next token to determine if it is 'void' or the start of a parameter list.
    Token next = peekToken();
    if (next.value() == "void") {
        // If 'void', get the token, create a node, and add it to the CST.
        Token voidToken = getToken();
        NodePtr voidNode = createNodePtr(voidToken);
        addToCST(voidNode, RightSibling);
    } else {
        // Parse the parameter list directly without creating a "ParameterList" node.
        parseParameterList();
    }
    
    // Expect and validate the right parenthesis ')' token.
    NodePtr rParenNode = expectToken(Token::Type::RParen, "Expected ')' after parameter list.");
    addToCST(rParenNode, RightSibling);
    
    // Expect and validate the left brace '{' token to start the procedure body.
    NodePtr lBraceNode = expectToken(Token::Type::LBrace, "Expected '{' to start the procedure body.");
    addToCST(lBraceNode, RightSibling);

    // Parse the procedure body (a compound statement).
    NodePtr compoundStatementNode = parseCompoundStatement();
    addToCST(compoundStatementNode, RightSibling);

    // Expect and validate the right brace '}' token to end the procedure.
    NodePtr rBraceNode = expectToken(Token::Type::RBrace, "Expected '}' to end the procedure.");
    addToCST(rBraceNode, RightSibling);
}

// Parses the list of parameters for a procedure or function.
NodePtr Parser::parseParameterList() {
    NodePtr firstParam = nullptr; // Will point to the first parameter node.
    NodePtr lastParam = nullptr;  // Tracks the last parameter node added to chain the next one as its right sibling.

    // Loop until a ')' token is encountered which indicates the end of the parameter list.
    while (true) {
        Token dataTypeToken = getToken();
        // If ')' is encountered, the parameter list is complete.
        if (dataTypeToken.type() == Token::Type::RParen) {
            current--; // Put back the ')' token for the calling function.
            break;
        }

        // Check that the current token is a valid data type.
        if (!isDataType(dataTypeToken.value())) {
            cerr << "Expected a data type in parameter list, found '" << dataTypeToken.value()
                 << "' at line " << dataTypeToken.lineNum() << "." << endl;
            exit(1); // Terminate on syntax error.
        }

        // Get the next token, which should be the identifier for the parameter.
        Token paramNameToken = getToken();
        if (paramNameToken.type() != Token::Type::Identifier) {
            cerr << "Expected an identifier for parameter name, found '"
                 << paramNameToken.value() << "' at line " << paramNameToken.lineNum() << "." << endl;
            exit(1); // Terminate on syntax error.
        }

        // Create a node for the data type and the parameter name.
        NodePtr dataTypeNode = createNodePtr(dataTypeToken);
        NodePtr paramNameNode = createNodePtr(paramNameToken);

        // Link the identifier node as the right sibling of the data type node.
        dataTypeNode->addRightSibling(paramNameNode);

        // If this is the first parameter, set the firstParam pointer.
        if (!firstParam) {
            firstParam = dataTypeNode;
        }

        // Chain the parameters: set the last parameter's right sibling to the current data type node.
        if (lastParam) {
            lastParam->addRightSibling(dataTypeNode);
        }
        // Update the last parameter node to be the current identifier node.
        lastParam = paramNameNode;

        // If the next token is a comma, consume it to move on to the next parameter.
        if (peekToken().type() == Token::Type::Comma) {
            getToken(); // Consume the comma token.
        }
    }

    // Return the head of the linked list of parameters.
    return firstParam;
}

// A helper method to consume the next token and validate its type
// Also add the expected token to the CST if it matches.
NodePtr Parser::expectToken(Token::Type expectedType, const std::string &errorMessage) {
    Token t = getToken();
    if (t.type() != expectedType) {
        cerr << errorMessage << " Found '" << typeToString(t.type())
             << "' at line " << t.lineNum() << "." << endl;
        exit(1);
    }
    NodePtr tokenNode = createNodePtr(t);
    addToCST(tokenNode, RightSibling); 
    return tokenNode;
}


// A helper method to peek at the current token without incrementing 'current'
Token Parser::peekToken() const {
    if (current >= tokens.size()) {
        throw std::runtime_error("Unexpected end of input while peeking at token.");
    }
    return tokens[current];
}

// NOT YET IMPLEMENTED FOR NOW
NodePtr Parser::parseCompoundStatement() {
    // Placeholder 
    return nullptr;
}

void Parser::parseExpression() { }

void Parser::parseSelectionStatement() {
    // Used for parsing selection statements (if-else)
}

void Parser::parseNumericalExpression() {
}

void Parser::parseBooleanExpression() {
}


bool isDataType(string id) {
    if (id == "char" || id == "int" || id == " bool")
        return true;
    return false;
}


bool isReserved(string id) {
    if (id == "char" || id == "int" || id == "bool" 
        || id == "void" || id =="function" || id == "procedure" || id == "main"
        || id == "return" || id == "printf" || id == "getchar" 
        || id == "if" || id == "else" || id == "for" || id == "while"
        || id == "TRUE" || id == "FALSE")
        return true;
    return false;
}
