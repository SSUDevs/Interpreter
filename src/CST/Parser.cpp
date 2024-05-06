#include "Parser.h"
#include "../ErrorHandler/ErrorHandler.h"
#include <iostream>
#include <string>

using namespace std;

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens) {}

NodePtr Parser::parse() {

    while (current < tokens.size()) {

        Token t = peekToken();

        if (t.type() == Token::Type::Identifier) {
            string tokenValue = t.value();
            if (isDataType(tokenValue)) {
                parseDeclaration();
            } else if (tokenValue == "procedure") {
                parseProcedure();
            } else if (tokenValue == "function") {
                parseFunction();
            } else { // error, global scope can only contain global variable
                // declarations, procedures, and functions
                _globalErrorHandler.handle(2, t.lineNum());
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

    Token currToken = peekToken();

    if (match(Token::Type::Identifier, currToken) &&
        isDataType(currToken.value())) {
        addToCST(createNodePtr(getToken()),
                 LeftChild); // add data type id to CST

        parseIDENTIFIER_AND_IDENTIFIER_ARRAY_LIST(); // add list of identifiers

        // semicolon check and add
        currToken = getToken();
        if (!match(Token::Type::Semicolon, currToken)) { // ERROR reserved name
            _globalErrorHandler.handle(32, currToken.lineNum());
        }
        addToCST(createNodePtr(currToken), RightSibling); // add name id to CST
    }
}

void Parser::parseIDENTIFIER_AND_IDENTIFIER_ARRAY_LIST() {

    while (match(Token::Type::Identifier, peekToken())) {
        parseIDENTIFIER_ARRAY_LIST();
        if (match(Token::Type::Identifier, peekToken()))
            parseIDENTIFIER_LIST();
    }
}

void Parser::parseIDENTIFIER_ARRAY_LIST() {
    Token currToken = peekToken();
    Token nextToken = peekAhead(1);
    bool foundEnd = false;

    while (match(Token::Type::Identifier, currToken) && !foundEnd) {
        if (isReserved(currToken.value())) { // check reserved
            _globalErrorHandler.handle(3, currToken.lineNum());
        }

        if (match(Token::Type::LBracket, nextToken)) {
            addToCST(createNodePtr((getToken())),
                     RightSibling); // add array name
            addToCST(createNodePtr((getToken())),
                     RightSibling); // add left bracket

            Token num = getToken();
            if (isReserved(num.value())) { // check reserved
                _globalErrorHandler.handle(3, currToken.lineNum());
            }
            if (num.value()[0] == '-' &&
                !match(Token::Type::Identifier,
                       num)) { // ERROR negative array size
                _globalErrorHandler.handle(4, num.lineNum());
            }
            addToCST(createNodePtr((num)),
                     RightSibling); // add num/variable name

            nextToken = getToken(); // get right bracket
            if (!match(Token::Type::RBracket,
                       nextToken)) { // incomplete bracket
                _globalErrorHandler.handle(5, nextToken.lineNum());
            }
            addToCST(createNodePtr((nextToken)),
                     RightSibling); // add right bracket

            nextToken = peekToken();
            if (match(Token::Type::Comma, nextToken)) {
                addToCST(createNodePtr((getToken())),
                         RightSibling); // add comma
                currToken = peekToken();
                nextToken = peekAhead(1);
            } else {
                foundEnd = true;
            }
        } else {
            foundEnd = true;
        }
    }
}

void Parser::parseIDENTIFIER_LIST() {
    Token currToken = peekToken();
    Token nextToken = peekAhead(1);

    bool foundEnd = false;

    while (match(Token::Type::Identifier, currToken) && !foundEnd) {
        if (isReserved(currToken.value())) {
            _globalErrorHandler.handle(3, currToken.lineNum());
        }

        // next token not bracket
        if (!match(Token::Type::LBracket, nextToken)) {
            addToCST(createNodePtr((getToken())),
                     RightSibling); // add variable name
            if (match(Token::Type::Comma, nextToken)) {
                addToCST(createNodePtr((getToken())),
                         RightSibling); // add comma
                currToken = peekToken();
                nextToken = peekAhead(1);
            } else {
                foundEnd = true;
            }
        } else {
            foundEnd = true;
        }
    }
}

void Parser::parseBlockStatement() {
    Token currToken = peekToken();
    if (!match(Token::Type::LBrace, currToken)) {
        _globalErrorHandler.handle(6, currToken.lineNum());
    }

    addToCST(createNodePtr(getToken()), LeftChild);

    parseCompoundStatement(); // add statements

    currToken = peekToken();
    if (!match(Token::Type::RBrace, currToken)) {
        _globalErrorHandler.handle(6, currToken.lineNum());
    }

    addToCST(createNodePtr(getToken()), LeftChild);
}

void Parser::parseProcedure() {
    addToCST(createNodePtr(getToken()),
             LeftChild); // add 'procedure' identifier to CST
    Token identifier = getToken();
    if (identifier.type() != Token::Type::Identifier) {
        _globalErrorHandler.handle(7, identifier.lineNum());
    }

    if (isReserved(identifier.value()) && identifier.value() != "main") {
        _globalErrorHandler.handle(3, identifier.lineNum());
    }
    // Create a procedure declaration node with identifier and add to CST
    addToCST(createNodePtr(identifier), RightSibling);

    NodePtr lParenNode =
        expectToken(Token::Type::LParen, "Expected '(' after procedure name.");
    addToCST(lParenNode, RightSibling);

    // See if next token is 'void' or params
    Token next = peekToken();
    if (next.value() == "void") {
        // If 'void', get the token, create a node, and add it to CST
        Token voidToken = getToken();
        addToCST(createNodePtr(voidToken), RightSibling);
    } else {
        parseParameterList();
    }

    NodePtr rParenNode =
        expectToken(Token::Type::RParen, "Expected ')' after parameter list.");
    addToCST(rParenNode, RightSibling);

    NodePtr lBraceNode = expectToken(
        Token::Type::LBrace, "Expected '{' to start the procedure body.");
    addToCST(lBraceNode, LeftChild);

    // Parse the procedure body (a compound statement).
    parseCompoundStatement();

    NodePtr rBraceNode =
        expectToken(Token::Type::RBrace, "Expected '}' to end the procedure.");
    addToCST(rBraceNode, LeftChild);
}

void Parser::parseFunction() {
    addToCST(createNodePtr(getToken()),
             LeftChild); // add 'function' identifier to CST
    Token return_type = getToken();

    if (!isDataType(return_type.value())) {
        _globalErrorHandler.handle(8, return_type.lineNum());
    }

    addToCST(createNodePtr(return_type), RightSibling);

    Token identifier = getToken();
    if (identifier.type() != Token::Type::Identifier) {
        _globalErrorHandler.handle(7, identifier.lineNum());
    }

    if (isReserved(identifier.value())) {
        _globalErrorHandler.handle(3, identifier.lineNum());
    }

    addToCST(createNodePtr(identifier), RightSibling);

    NodePtr lParenNode =
        expectToken(Token::Type::LParen, "Expected '(' after procedure name.");
    addToCST(lParenNode, RightSibling);

    // See if next token is 'void' or params
    Token next = peekToken();
    if (next.value() == "void") {
        // If 'void', get the token, create a node, and add it to CST
        Token voidToken = getToken();
        addToCST(createNodePtr(voidToken), RightSibling);
    } else {
        parseParameterList();
    }
    NodePtr rParenNode =
        expectToken(Token::Type::RParen, "Expected ')' after parameter list.");
    addToCST(rParenNode, RightSibling);

    NodePtr lBraceNode = expectToken(
        Token::Type::LBrace, "Expected '{' to start the procedure body.");
    addToCST(lBraceNode, LeftChild);

    // Parse the procedure body (a compound statement).
    parseCompoundStatement();

    NodePtr rBraceNode =
        expectToken(Token::Type::RBrace, "Expected '}' to end the procedure.");
    addToCST(rBraceNode, LeftChild);
}

void Parser::parseParameterList() {
    bool expectParameter = true;
    while (expectParameter) {
        // Expect a data type specifier
        Token dataTypeToken = getToken();
        if (!isDataType(dataTypeToken.value())) {
            _globalErrorHandler.handle(9, dataTypeToken.lineNum());
        }
        addToCST(createNodePtr(dataTypeToken), RightSibling);

        // Expect an identifier after data type
        Token identifierToken = getToken();
        if (identifierToken.type() != Token::Type::Identifier) {
            _globalErrorHandler.handle(10, identifierToken.lineNum());
        }

        if (isReserved(identifierToken.value())) {
            _globalErrorHandler.handle(3, identifierToken.lineNum());
        }
        addToCST(createNodePtr(identifierToken), RightSibling);

        // Check for array syntax
        Token nextToken = peekToken();
        if (nextToken.type() == Token::Type::LBracket) {
            // Consume '['
            getToken();
            addToCST(createNodePtr(nextToken), RightSibling);

            // Expect and consume the array size (a whole number)
            Token arraySizeToken = getToken();
            if (arraySizeToken.type() != Token::Type::Integer) {
                _globalErrorHandler.handle(11, arraySizeToken.lineNum());
            }
            addToCST(createNodePtr(arraySizeToken), RightSibling);

            // Expect and consume ']'
            Token closeBracketToken = getToken();
            if (closeBracketToken.type() != Token::Type::RBracket) {
                _globalErrorHandler.handle(5, closeBracketToken.lineNum());
            }
            addToCST(createNodePtr(closeBracketToken), RightSibling);

            // Update nextToken to peek at the next token after the array syntax
            nextToken = peekToken();
        }

        // Handle end of parameter or continuation with comma
        if (nextToken.type() == Token::Type::RParen) {
            // End of parameter list
            expectParameter = false;
        } else if (nextToken.type() == Token::Type::Comma) {
            // Consume comma and continue
            getToken(); // This consumes the comma token, moving to the next
                        // parameter
            addToCST(createNodePtr(nextToken), RightSibling);
        } else {
            _globalErrorHandler.handle(12, nextToken.lineNum());
        }
    }
}

void Parser::processFunctionCall() {
    // Process Function name
    NodePtr functionName = expectToken(Token::Type::Identifier,
                                       "Expected identifier for function call");
    addToCST(functionName, RightSibling);

    NodePtr LParenNode =
        expectToken(Token::Type::LParen, "Expected '(' after function call");
    addToCST(LParenNode, RightSibling);

    // Now parse the argument list
    parseFunctionArguments();

    NodePtr closingParen = expectToken(Token::Type::RParen, "Expected ')'");
    addToCST(closingParen, RightSibling);
}

void Parser::parseFunctionArguments() {
    // Ends the function call with the ending RParen
    while (peekToken().type() != Token::Type::RParen) {
        Token argToken = peekToken();

        // Check if the argument is an identifier possibly followed by an array
        // index
        if (argToken.type() == Token::Type::Identifier) {
            // Add the identifier
            addToCST(createNodePtr(getToken()), RightSibling);

            // Check if the next token is array indexing
            if (peekToken().type() == Token::Type::LBracket) {
                // Add the '['
                addToCST(createNodePtr(getToken()), RightSibling);

                // Parse the index expression
                parseExpression();

                // Expect and Add ']'
                NodePtr rBracketNode =
                    expectToken(Token::Type::RBracket, "Expected ']'");
                addToCST(rBracketNode, RightSibling);
            }
        } else {
            _globalErrorHandler.handle(7, argToken.lineNum());
        }

        // Check if there's another argument after a comma
        if (peekToken().type() == Token::Type::Comma) {
            addToCST(createNodePtr(getToken()), RightSibling); // Add the comma
        }
    }
}

void Parser::parseCompoundStatement() {

    // parse statements until next token is a right brace
    while (!match(Token::Type::RBrace, peekToken()))
        parseStatement();
}

void Parser::parseStatement() {
    Token next = peekToken();

    // must be an identifier
    if (!match(Token::Type::Identifier, next)) {
        _globalErrorHandler.handle(13, next.lineNum());
    }

    // these reserved words have statements
    if (isReserved(next.value())) {
        if (isDataType(next.value()))
            parseDeclaration();
        else if (next.value() == "for" || next.value() == "while")
            parseIterationStatement();
        else if (next.value() == "if")
            parseSelectionStatement();
        else if (next.value() == "printf")
            parsePrintfStatement();
        else if (next.value() == "return")
            parseReturnStatement();
        else {
            _globalErrorHandler.handle(13, next.lineNum());
        }

    }
    // only possible statement that starts with unreserved word
    else {
        if (match(Token::Type::AssignmentOperator, peekAhead(1))) {
            parseAssignmentStatement();
        } else if (match(Token::Type::LBracket, peekAhead(1))) {
            parseAssignmentStatement();
        } else
            parseProcedureStatement();
    }
}

void Parser::parseProcedureStatement() {
    Token token = peekToken();

    if (!match(Token::Type::Identifier, token) || isReserved(token.value())) {
        _globalErrorHandler.handle(3, token.lineNum());
    }

    // procedure name
    addToCST(createNodePtr(getToken()), LeftChild);
    // (
    addToCST(expectToken(Token::Type::LParen, "Expected '('"), RightSibling);
    // param list
    parseIDENTIFIER_AND_IDENTIFIER_ARRAY_LIST();
    // )
    addToCST(expectToken(Token::Type::RParen, "Expected ')'"), RightSibling);
    // ;
    addToCST(expectToken(Token::Type::Semicolon, "Expected ';'"), RightSibling);
}

void Parser::parseSelectionStatement() {

    // if
    Token ifToken = getToken();
    if (ifToken.value() != "if") {
        _globalErrorHandler.handle(14, ifToken.lineNum());
    }
    addToCST(createNodePtr(ifToken), LeftChild);

    // (
    NodePtr LParenNode = expectToken(Token::Type::LParen,
                                     "Expected '(' before boolean expression");
    addToCST(LParenNode, RightSibling);

    // Parse the boolean expression within the if statement.
    parseExpression();

    // )
    NodePtr RParenNode = expectToken(Token::Type::RParen,
                                     "Expected ')' after boolean expression");
    addToCST(RParenNode, RightSibling);

    // The statement or block statement that follows.
    parseStatementOrBlock(); // A helper function that decides whether it's a
                             // simple statement or a block statement.

    // Check for "else"
    Token next = peekToken();
    if (next.value() == "else") {
        // Consume the "else" token.
        NodePtr elseNode = createNodePtr(getToken());
        addToCST(elseNode, LeftChild);

        // Parse the statement or block statement following "else".
        parseStatementOrBlock(); // Reuse the helper function for the "else"
                                 // part.
    }
}

void Parser::parseStatementOrBlock() {
    // Peek at the next token to decide between a simple statement and a block
    // statement.
    Token next = peekToken();
    if (match(Token::Type::LBrace, next)) {
        // If the next token is '{', it's a block statement.
        parseBlockStatement();
    } else {
        // it's a single statement.
        parseStatement();
    }
}

void Parser::parseExpression() {

    Token currToken = peekToken();

    // Check for function call
    if (currToken.type() == Token::Type::Identifier &&
        peekAhead(1).type() == Token::Type::LParen) {
        processFunctionCall();
        return; // Exit early after processing the function call
    }

    // Handling unary operators (minus and logical NOT)
    if (match(Token::Type::Minus, currToken) ||
        match(Token::Type::BooleanNot, currToken)) {
        addToCST(createNodePtr(getToken()),
                 RightSibling); // Add '-' or '!' to CST
        currToken =
            peekToken(); // Refresh currToken after consuming the operator
    }

    // If the current token is '('
    if (match(Token::Type::LParen, currToken)) {
        getToken();
        addToCST(createNodePtr(currToken), RightSibling);
        parseExpression();

        NodePtr rParenNode = expectToken(Token::Type::RParen, "Expected ')'");
        addToCST(rParenNode, RightSibling);

        if (isOperator(peekToken())) {
            Token operatorToken = getToken();
            addToCST(createNodePtr(operatorToken), RightSibling);
            parseExpression();
        }

    } else if (!isReserved(currToken.value()) ||
               currToken.type() == Token::Type::DoubleQuotedString ||
               currToken.type() ==
                   Token::Type::SingleQuotedString) { // If the token is an
                                                      // operand and it's not
                                                      // reserved
        addToCST(createNodePtr(currToken), RightSibling);
        getToken();

        Token nextToken = peekToken();
        if (match(Token::Type::LParen, nextToken) &&
            currToken.type() == Token::Type::Identifier) {
            getToken();
            addToCST(createNodePtr(nextToken), RightSibling);

            if (peekAhead(1).type() == Token::Type::Comma) {
                // If the next token indicates a parameter list
                parseIDENTIFIER_AND_IDENTIFIER_ARRAY_LIST();
            } else {
                // Otherwise, it's an expression within parentheses
                parseExpression();
            }
            NodePtr closingRParen =
                expectToken(Token::Type::RParen, "Expected ')'");
            addToCST(closingRParen, RightSibling);
        }

        if (peekToken().type() == Token::Type::LBracket) {
            // Array indexing
            addToCST(createNodePtr(getToken()), RightSibling); // Consume '['
            parseExpression(); // Parse the index expression
            addToCST(expectToken(Token::Type::RBracket, "Expected ']'"),
                     RightSibling);
        }

        // Check for an operator after the operand
        if (isOperator(peekToken())) {
            Token operatorToken = getToken();
            addToCST(createNodePtr(operatorToken), RightSibling);
            parseExpression();
        }
    } else {
        _globalErrorHandler.handle(15, currToken.lineNum());
    }
}

void Parser::parseAssignmentStatement() {
    Token currtoken = peekToken();
    Token next = peekAhead(1);

    if (next.type() != Token::Type::AssignmentOperator &&
        next.type() != Token::Type::LBracket) {
        _globalErrorHandler.handle(16, next.lineNum());

    }
    // array assignment
    else if (next.type() == Token::Type::LBracket) {
        // add identifier
        addToCST(createNodePtr(getToken()), LeftChild);

        // [
        addToCST(createNodePtr(getToken()), RightSibling);

        next = peekToken();

        if (next.type() != Token::Type::Integer &&
            next.type() != Token::Type::Identifier) {
            _globalErrorHandler.handle(17, next.lineNum());
        }

        if (isReserved(next.value())) {
            _globalErrorHandler.handle(3, next.lineNum());
        }

        // array index
        addToCST(createNodePtr(getToken()), RightSibling);

        // ]
        addToCST(expectToken(Token::Type::RBracket, "Expected ']'"),
                 RightSibling);

        // =
        addToCST(expectToken(Token::Type::AssignmentOperator, "Expected ']'"),
                 RightSibling);
    }
    // simple assignment
    else {
        // identifier
        addToCST(createNodePtr(getToken()), LeftChild);
        // =
        addToCST(createNodePtr(getToken()), RightSibling);
    }
    Token token = peekToken();

    if (token.type() == Token::Type::SingleQuotedString ||
        token.type() == Token::Type::DoubleQuotedString) {
        token = getToken();
        addToCST(createNodePtr(token), RightSibling);
    }
    else {
        parseExpression();
    }

    token = getToken();
    if (token.type() != Token::Type::Semicolon) {
        _globalErrorHandler.handle(18, next.lineNum());
    }
    addToCST(createNodePtr(token), RightSibling);
} // not done

void Parser::parseInLineStatement() {
    Token next = peekToken();

    if (!match(Token::Type::Identifier, next)) {
        _globalErrorHandler.handle(19, next.lineNum());
    }

    if (isReserved(next.value())) {
        _globalErrorHandler.handle(3, next.lineNum());
    }

    // identifier
    addToCST(createNodePtr(getToken()), RightSibling);
    // =
    addToCST(expectToken(Token::Type::AssignmentOperator, "Error expected '='"),
             RightSibling);
    // expression
    parseExpression();
}

void Parser::parseIterationStatement() {
    Token next = peekToken();

    if (!match(Token::Type::Identifier, next)) {
        _globalErrorHandler.handle(20, next.lineNum());
    }

    if (next.value() == "for") {
        // for
        addToCST(createNodePtr(getToken()), LeftChild);
        // (
        addToCST(expectToken(Token::Type::LParen, "Syntax error: missing '('"),
                 RightSibling);
        // in line statement
        parseInLineStatement();
        // semicolon
        addToCST(
            expectToken(Token::Type::Semicolon, "Syntax error: missing ';'"),
            RightSibling);
        // expression
        parseExpression();
        // semicolon
        addToCST(
            expectToken(Token::Type::Semicolon, "Syntax error: missing ';'"),
            RightSibling);
        // in line statement
        parseInLineStatement();
        // )
        addToCST(expectToken(Token::Type::RParen, "Syntax error: missing ')'"),
                 RightSibling);

        next = peekToken();

        // finish with a block statement or a single statement
        parseStatementOrBlock();

    } else if (next.value() == "while") {
        // while
        addToCST(createNodePtr(getToken()), LeftChild);
        // (
        addToCST(expectToken(Token::Type::LParen, "Syntax error: missing '('."),
                 RightSibling);
        // expression
        parseExpression();
        // )
        addToCST(expectToken(Token::Type::RParen, "Syntax error: missing ')'."),
                 RightSibling);

        // finish with a block statement or a single statement
        parseStatementOrBlock();

    } else {
        _globalErrorHandler.handle(20, next.lineNum());
    }
}

void Parser::parsePrintfStatement() {
    // printf
    addToCST(createNodePtr(getToken()), LeftChild);

    // (
    addToCST(expectToken(Token::Type::LParen, "Expected '(' after 'printf'"),
             RightSibling);

    Token nextToken = peekToken();
    if (!match(Token::Type::DoubleQuotedString, nextToken) &&
        !match(Token::Type::SingleQuotedString, nextToken)) {
        _globalErrorHandler.handle(21, nextToken.lineNum());
    }
    // "string"
    Token stringToken = getToken();
    addToCST(createNodePtr(stringToken), RightSibling);

    // ,
    nextToken = peekToken();
    if (match(Token::Type::Comma, nextToken)) {
        addToCST(createNodePtr(getToken()), RightSibling);
        parseIDENTIFIER_AND_IDENTIFIER_ARRAY_LIST();
    }

    // )
    addToCST(
        expectToken(Token::Type::RParen, "Expected ')' after printf statement"),
        RightSibling);
    // ;
    addToCST(expectToken(Token::Type::Semicolon,
                         "Expected ';' at the end of printf statement"),
             RightSibling);
}

void Parser::parseReturnStatement() {
    //    NodePtr returnNode = expectToken(Token::Type::Return, "Syntax error:
    //    Expected 'return'");
    Token return_token = getToken();

    if (return_token.value() != "return") {
        _globalErrorHandler.handle(22, return_token.lineNum());
    }
    addToCST(createNodePtr(return_token), LeftChild);

    Token nextToken = peekToken();
    if (peekToken().type() == Token::Type::SingleQuotedString ||
        peekToken().type() == Token::Type::DoubleQuotedString) {
        addToCST(createNodePtr(getToken()), RightSibling);
    } else {
        parseExpression();
    }

    // Regardless of whether an Identifier was found, a semicolon is expected
    Token semiToken = getToken();
    if (semiToken.type() != Token::Type::Semicolon) {
        _globalErrorHandler.handle(18, semiToken.lineNum());
    }
    addToCST(createNodePtr(semiToken),
             RightSibling); // Adjust insertion mode as needed
}

// A helper method to consume the next token and validate its type
// Also add the expected token to the CST if it matches.
NodePtr Parser::expectToken(Token::Type expectedType,
                            const std::string &errorMessage) {
    Token t = getToken();
    if (t.type() != expectedType) {
        cerr << errorMessage << " Found '" << Token::typeToString(t.type())
             << "' at line " << t.lineNum() << "." << endl;
        exit(100);
    }
    // Create a NodePtr from the token and return it
    return createNodePtr(t);
}

// Helper method to peek at current token without incrementing 'current'
Token Parser::peekToken() const {
    if (current >= tokens.size()) {
        throw std::runtime_error(
            "Unexpected end of input while peeking at token.");
    }
    return tokens[current];
}

// A helper method to peek ahead more than one token without incrementing
// 'current'
Token Parser::peekAhead(int offset) const {
    if (current + offset >= tokens.size()) {
        throw std::runtime_error(
            "Unexpected end of input while peeking at token.");
    }
    return tokens[current + offset];
}

bool isDataType(string id) {
    if (id == "char" || id == "int" || id == "bool")
        return true;
    return false;
}

bool isReserved(string id) {
    if (id == "char" || id == "int" || id == "bool" || id == "void" ||
        id == "function" || id == "procedure" || id == "main" ||
        id == "return" || id == "printf" || id == "getchar" || id == "if" ||
        id == "else" || id == "for" || id == "while")
        return true;
    return false;
}

bool isOperator(Token t) {
    if (t.type() == Token::Type::Plus || t.type() == Token::Type::Minus ||
        t.type() == Token::Type::Slash || t.type() == Token::Type::Asterisk ||
        t.type() == Token::Type::Modulo || t.type() == Token::Type::Caret ||
        t.type() == Token::Type::Lt || t.type() == Token::Type::Gt ||
        t.type() == Token::Type::LtEqual || t.type() == Token::Type::GtEqual ||
        t.type() == Token::Type::BooleanAnd ||
        t.type() == Token::Type::BooleanOr ||
        t.type() == Token::Type::BooleanNot ||
        t.type() == Token::Type::BooleanEqual ||
        t.type() == Token::Type::BooleanNotEqual)
        return true;
    return false;
}