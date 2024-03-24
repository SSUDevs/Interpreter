#include "Parser.h"
#include <iostream>
using namespace std;
// Use make_shared to dynamically allocate Node instances.
// When a new node is created, it's managed by a shared_ptr.

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens) {}

NodePtr Parser::parse() {

    while (current < tokens.size()) {

        Token t = getToken();

        if (t.type() == Token::Type::Identifier) {
            string tokenValue = t.value();

            if (isDataType(tokenValue)) {
                parseDeclaration();
            } else if (tokenValue == "procedure") {
                parseProcedure();
            } else if (tokenValue == "function") {
                pasrseFunction();
            } else { // error, global scope can only contain global variable
                     // declarations, procedures, and functions
                cerr << "Invalid syntax in global scope at line " << t.lineNum()
                     << endl;
                exit(1);
            }
        }
    }

    return root;
}

Token Parser::getToken() {
    if (current < tokens.size()) {
        return tokens[current++];
    } else {
        throw std::runtime_error("Unexpected end of input");
    }
}

void Parser::addToCST(NodePtr node, InsertionMode mode) {
    if (!root) {
        root = node;
    } else {
        if (mode == LeftChild)
            lastNode->leftChild = node;
        else
            lastNode->rightSibling = node;
    }
    lastNode = node;
}

NodePtr Parser::createNodePtr(const Token &token) {
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

    if (match(Token::Type::Identifier, currToken)) {
        addToCST(createNodePtr(currToken),
                 LeftChild); // add data type id to CST

        currToken = getToken();
        if (isReserved(currToken.value())) { // ERROR reserved name
            cerr << "Syntax error on line " << currToken.lineNum()
                 << ": reserved word \"" << currToken.value()
                 << "\" cannot be used for a variable name." << endl;
            exit(1);
        }
        addToCST(createNodePtr(currToken), RightSibling); // add name id to CST

        currToken = getToken();
        if (!match(Token::Type::Semicolon, currToken)) { // ERROR no semicolon
            cerr << "Syntax error on line " << currToken.lineNum()
                 << ": missing ';'." << endl;
            exit(1);
        }
        addToCST(createNodePtr(currToken), RightSibling); // add ; to CST
    } else { // ERROR invalid declaration type
        cerr << "Syntax error on line " << currToken.lineNum()
             << ": not a vlaid type" << endl;
        exit(1);
    }
}

// NOTES:
// <PROCEDURE_DECLARATION> ::= procedure <IDENTIFIER> <L_PAREN>
// <PARAMETER_LIST> <R_PAREN> < L_BRACE> <COMPOUND_STATEMENT> <R_BRACE>
// | procedure <IDENTIFIER> <L_PAREN> void <R_PAREN> < L_BRACE>
// <COMPOUND_STATEMENT> <R_BRACE>
void Parser::parseProcedure() {
    // The current token must have been the 'procedure' keyword to get here
    // Next, expect an identifier token for the procedure name
    Token identifier = getToken();
    if (identifier.type() != Token::Type::Identifier) {
        cerr << "Syntax error: Expected an identifier for the procedure name, "
                "found '"
             << identifier.value() << "' at line " << identifier.lineNum()
             << "." << endl;
        exit(1);
    }

    // Create a new node for the procedure declaration
    NodePtr procedureNode = createNodePtr(identifier);

    // Expect a left parenthesis '(' starting the parameter list
    expectToken(Token::Type::LParen, "Expected '(' after procedure name.");

    // Check for 'void' or parse the parameter list
    Token next = peekToken();

    if (next.value() == "void") {
        // No parameters to parse, if 'void'
        getToken(); // take out the 'void'
    } else {
        // Parse the parameter list if it's not 'void'
        parseParameterList();
        // The parameter list will be attached inside the parseParameterList
        // function
    }

    // Expect a right parenthesis ')' ending the parameter list
    expectToken(Token::Type::RParen, "Expected ')' after parameter list.");
    // Expect a left brace '{' starting the procedure body
    expectToken(Token::Type::LBrace,
                "Expected '{' to start the procedure body.");

    // Parse the compound statement that is the procedure body
    NodePtr compoundStatementNode = parseCompoundStatement();
    // Attach the compound statement to the procedure node
    procedureNode->addLeftChild(compoundStatementNode);

    // Finally, expect a right brace '}' to end the procedure
    expectToken(Token::Type::RBrace, "Expected '}' to end the procedure.");

    // Add the procedure node to the CST containing the body as well attached to it
    addToCST(procedureNode, LeftChild); 
}

// A helper method to consume the next token and validate its type
void Parser::expectToken(Token::Type expectedType, const string &errorMessage) {
    Token t = getToken();
    if (t.type() != expectedType) {
        cerr << errorMessage << " Found '" << typeToString(t.type())
             << "' at line " << t.lineNum() << "." << endl;
        exit(1);
    }
}

void Parser::parseParameterList() {
    // Create a node to represent the parameter list in the CST
    NodePtr parameterListNode = std::make_shared<Node>(Token(Token::Type::ParameterList, "ParameterList"));

    // Peek at the next token to check if it's 'void', which means no parameters
    if (peekToken().value() == "void") {
        getToken(); // Consume the 'void' token
        // If the parameter list is just 'void', we may still create a parameter node to reflect this in the CST
        NodePtr voidNode = createNodePtr(Token(Token::Type::Void, "void"));
        parameterListNode->addLeftChild(voidNode);
    } else {
        // Parse the parameter list which is not 'void'
        // Loop until a ')' token is encountered which indicates the end of the parameter list
        while (peekToken().type() != Token::Type::RParen) {
            Token dataType = getToken();
            if (!isDataType(dataType.value())) {
                cerr << "Expected a data type in parameter list, found '" << dataType.value() 
                     << "' at line " << dataType.lineNum() << "." << endl;
                exit(1);
            }

            Token paramName = getToken();
            if (paramName.type() != Token::Type::Identifier) {
                cerr << "Expected an identifier for parameter name, found '" << paramName.value() 
                     << "' at line " << paramName.lineNum() << "." << endl;
                exit(1);
            }

            // Create nodes for the datatype and parameter name
            NodePtr typeNode = createNodePtr(dataType);
            NodePtr nameNode = createNodePtr(paramName);
            typeNode->addLeftChild(nameNode); // Link the identifier as the left child of the datatype node

            // Link the current parameter node as a sibling of the previous parameter node
            // If this is the first parameter, it becomes the left child of the parameter list node
            if (!parameterListNode->getLeftChild()) {
                parameterListNode->addLeftChild(typeNode);
            } else {
                // Find the last parameter node added
                NodePtr lastParam = parameterListNode->getLeftChild();
                while (lastParam->getRightSibling()) {
                    lastParam = lastParam->getRightSibling();
                }
                lastParam->addRightSibling(typeNode);
            }

            // If the next token is a comma, consume it and move on to the next parameter
            if (peekToken().type() == Token::Type::Comma) {
                getToken(); // Consume the comma token
            }
        }
    }

    // Once all parameters are processed or if it was 'void', we need to attach the parameter list node to the function/procedure node
    // Assuming 'lastNode' is the current function or procedure node
    lastNode->addLeftChild(parameterListNode);
}


// NOT YET IMPLEMENTED FOR NOW
void Parser::parseCompoundStatement() {
    return NodePtr nodePtr;
}

void Parser::parseExpression() {}

void Parser::parseSelectionStatement() {
    // Used for parsing selection statements (if-else)
}

void Parser::parseNumericalExpression() {}

void Parser::parseBooleanExpression() {}

bool isDataType(string id) {
    if (id == "char" || id == "int" || id == " bool")
        return true;
    return false;
}

bool isReserved(string id) {
    if (id == "char" || id == "int" || id == "bool" || id == "void" ||
        id == "function" || id == "procedure" || id == "main" ||
        id == "return" || id == "printf" || id == "getchar" || id == "if" ||
        id == "else" || id == "for" || id == "while" || id == "TRUE" ||
        id == "FALSE")
        return true;
    return false;
}