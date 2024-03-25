#ifndef PARSER_H
#define PARSER_H

#include "../Token/Token.h"
#include "Node.h" // Defines the concrete syntax tree
#include <vector>

class Parser {
    std::vector<Token> tokens;
    size_t current = 0;
    NodePtr root; // Root of the CST
    NodePtr lastNode;

    enum InsertionMode {
        LeftChild,
        RightSibling
    };

public:
    // Constructor (Using explicit to avoid accidental implicit conversions)
    explicit Parser(const std::vector<Token>& tokens);

    NodePtr parse(); 

private:
    Token getToken(); // Gets the current token and moves to the next
    bool match(Token::Type type, Token t); // Checks if the current token matches the given token type
    void addToCST(NodePtr node, InsertionMode mode);
    NodePtr createNodePtr(const Token& token);

    Token peekToken() const;
    void expectToken(Token::Type expectedType, const std::string &errorMessage);


    void parseProcedure();
    // void parseFunction();
    // NodePtr parseCompoundStatement() {

    void parseDeclaration();
    void parseIDENTIFIER_AND_IDENTIFIER_ARRAY_LIST();
    void parseIDENTIFIER_ARRAY_LIST();
    void parseIDENTIFIER_LIST();



    // Starting with this piece of the BNF
    // <EXPRESSION> ::= <BOOLEAN_EXPRESSION> | <NUMERICAL_EXPRESSION> 
    void parseExpression();

    void parseSelectionStatement(); // For IF statements

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
    void parseNumericalExpression();

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
    void parseBooleanExpression();

};

bool isDataType(std::string id);
bool isReserved(std::string id);

#endif // PARSER_H