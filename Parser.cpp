#include "Parser.h"
#include <iostream>
using namespace std;
// Use make_shared to dynamically allocate Node instances. 
// When a new node is created, it's managed by a shared_ptr.

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

NodePtr Parser::parse() {

    while (current < tokens.size()) {
        if (tokens[current].type() == Token::Type::Identifier) {
            string tokenValue = tokens[current].value();

            if (isDataType(tokenValue))
                addToCST(parseDeclaration(), LeftChild);
            else if (tokenValue == "procedure")
                addToCST(parseProcedure(), LeftChild);
            else if (tokenValue == "function")
                addToCST(pasrseFunction(), LeftChild);
            else { // error, global scope can only contain global variable declarations, procedures, and functions
                cerr << "Invalid syntax in global scope at line " << tokens[current].lineNum() << endl;
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

bool Parser::match(Token::Type type) {
    if (current < tokens.size() && tokens[current].type() == type) {
        ++current;
        return true;
    }
    return false;
}

NodePtr Parser::parseDeclaration() {
    return nullptr;
}

NodePtr Parser::parseProcedure() {

    return nullptr;
}

NodePtr Parser::pasrseFunction() {

    return nullptr;
}

NodePtr Parser::parseExpression() { return nullptr; }

NodePtr Parser::parseSelectionStatement() {
    // Used for parsing selection statements (if-else)
    return std::make_shared<Node>("SelectionStatement");
}

NodePtr Parser::parseNumericalExpression() {
    return std::make_shared<Node>("NumericalExpression");
}

NodePtr Parser::parseBooleanExpression() {
    return std::make_shared<Node>("BooleanExpression");
}


bool isDataType(string id) {
    if (id == "char" || id == "int" || id == " bool")
        return true;
    return false;
}