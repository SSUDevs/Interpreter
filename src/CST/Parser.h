#ifndef PARSER_H
#define PARSER_H

#include "../Token/Token.h"
#include "../Node/Node.h" 
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
    //peek ahead more than one tokens
    Token peekAhead(int offset = 0) const;

    NodePtr expectToken(Token::Type expectedType, const std::string &errorMessage);


    void parseProcedure();
    void parseFunction();
    void parseParameterList();
    void parseFunctionArguments();
    void processFunctionCall();

    void parseDeclaration();
    void parseIDENTIFIER_AND_IDENTIFIER_ARRAY_LIST();
    void parseIDENTIFIER_ARRAY_LIST();
    void parseIDENTIFIER_LIST();

    void parseBlockStatement();
    void parseCompoundStatement();
    void parseStatement();
    void parseAssignmentStatement();    
    void parseInLineStatement();     
    void parseIterationStatement();  

    void parseSelectionStatement();     
    void parseStatementOrBlock();
    void parseProcedureStatement();
    void parseExpression();

    void parsePrintfStatement();        
    void parseReturnStatement();       
};

bool isDataType(std::string id);
bool isReserved(std::string id);
bool isOperator(Token t);

#endif // PARSER_H
