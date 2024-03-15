#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "Node.h" // Defines the concrete syntax tree
#include <vector>

class Parser {
    std::vector<Token> tokens;
    size_t current = 0;
    NodePtr root; // Root of the CST

public:
    Parser(const std::vector<Token>& tokens);\

    NodePtr parse(); 

private:
    // Starting with this piece of the BNF
    // <EXPRESSION> ::= <BOOLEAN_EXPRESSION> | <NUMERICAL_EXPRESSION> 
    NodePtr parseExpression(); 

    NodePtr parseNumericalExpression();

    NodePtr parseBooleanExpression();
};

#endif // PARSER_H
