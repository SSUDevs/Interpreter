#include "Parser.h"
#include <iostream>
// Use make_shared to dynamically allocate Node instances. 
// When a new node is created, it's managed by a shared_ptr.

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

NodePtr Parser::parse() {
    // Parsing logic...
}

Token Parser::getToken() {
    if (current < tokens.size()) {
        return tokens[current++]; // Corrected to avoid returning a reference
    } else {
        throw std::runtime_error("Unexpected end of input");
    }
}

bool Parser::match(Token::Type type) {
    if (current < tokens.size() && tokens[current].type() == type) {
        ++current;
        return true;
    }
    return false;
}

NodePtr Parser::parseExpression() {}

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


