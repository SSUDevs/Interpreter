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
    // Constructor (Using explicit to avoid accidental implicit conversions)
    explicit Parser(const std::vector<Token>& tokens);

    NodePtr parse(); 

private:
    Token getToken(); // Gets the current token and moves to the next
    bool match(Token::Type type); // Checks if the current token matches the given token type

    // Starting with this piece of the BNF
    // <EXPRESSION> ::= <BOOLEAN_EXPRESSION> | <NUMERICAL_EXPRESSION> 
    NodePtr parseExpression(); 

    NodePtr parseSelectionStatement(); // For IF statements

    // NOTES:
    // <NUMERICAL_EXPRESSION> ::= <NUMERICAL_OPERAND> | <L_PAREN> 
    // <NUMERICAL_OPERAND> <R_PAREN> | <NUMERICAL_OPERAND> 
    // <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION> | <L_PAREN> 
    // <NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION> 
    // <R_PAREN> | <NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <L_PAREN> 
    // <NUMERICAL_EXPRESSION> <R_PAREN> <NUMERICAL_OPERAND> 
    // <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION> | <L_PAREN> 
    // <NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION> 
    // <R_PAREN> | <NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <L_PAREN> 
    // <NUMERICAL_EXPRESSION> <R_PAREN>
    NodePtr parseNumericalExpression();

    // NOTES:
    // <BOOLEAN_EXPRESSION> ::= 
    // <BOOLEAN_TRUE> | <BOOLEAN_FALSE> | <IDENTIFIER> | 
    // <IDENTIFIER> <BOOLEAN_OPERATOR> <BOOLEAN_EXPRESSION> |  
    // <L_PAREN> <IDENTIFIER> <BOOLEAN_OPERATOR> <BOOLEAN_EXPRESSION> <R_PAREN> | 
    // <NUMERICAL_EXPRESSION> <BOOLEAN_EQUAL> <NUMERICAL_EXPRESSION> | 
    // <NUMERICAL_EXPRESSION> <BOOLEAN_NOT_EQUAL> <NUMERICAL_EXPRESSION> | 
    // <NUMERICAL_EXPRESSION> <LT_EQUAL> <NUMERICAL_EXPRESSION> | 
    // <NUMERICAL_EXPRESSION> <GT_EQUAL> <NUMERICAL_EXPRESSION> | 
    // <NUMERICAL_EXPRESSION> <LT> <NUMERICAL_EXPRESSION> | 
    // <NUMERICAL_EXPRESSION> <GT> <NUMERICAL_EXPRESSION>
    NodePtr parseBooleanExpression();
};

#endif // PARSER_H
