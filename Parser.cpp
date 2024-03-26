#include "Parser.h"
#include <iostream>
using namespace std;
// Use make_shared to dynamically allocate Node instances.
// When a new node is created, it's managed by a shared_ptr.

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
                cerr << "Invalid syntax in global scope at line " << t.lineNum()
                     << " with identifier: " << tokenValue << endl;
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
    cout<<"Adding token with value "<<node->Value().value()<<" to tree with mode "<< mode <<endl;

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

    if (match(Token::Type::Identifier, currToken) && isDataType(currToken.value())) {
        addToCST(createNodePtr(getToken()),LeftChild); // add data type id to CST

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

    while (!match(Token::Type::Semicolon, peekToken())) {
        parseIDENTIFIER_ARRAY_LIST();
        if (!match(Token::Type::Semicolon, peekToken()))
            parseIDENTIFIER_LIST();
    }
}

void Parser::parseIDENTIFIER_ARRAY_LIST() {
    Token currToken = getToken();
    Token nextToken = getToken();
    bool foundEnd = false;

    while (match(Token::Type::Identifier, currToken) && !foundEnd) {
        if (isReserved(currToken.value())) { // check reserved
            cerr << "Syntax error on line " << currToken.lineNum()
                 << ": reserved word \"" << currToken.value()
                 << "\" cannot be used for a variable name." << endl;
            exit(9);
        }

        if (match(Token::Type::LBracket, nextToken)) {
            addToCST(createNodePtr((currToken)),
                     RightSibling); // add array name
            addToCST(createNodePtr((nextToken)),
                     RightSibling); // add left bracket

            Token num = getToken();
            if (isReserved(num.value())) { // check reserved
                cerr << "Syntax error on line " << num.lineNum()
                     << ": reserved word \"" << num.value()
                     << "\" cannot be used for a variable name." << endl;
                exit(10);
            }
            if (stoi(num.value()) <= 0 &&
                !match(Token::Type::Identifier,
                       num)) { // ERROR negative array size
                cerr << "Syntax error on line " << num.lineNum()
                     << ": array declaration size must be a positive integer."
                     << endl;
                exit(11);
            }
            addToCST(createNodePtr((num)),
                     RightSibling); // add num/variable name

            nextToken = getToken(); // get right bracket
            if (!match(Token::Type::RBracket,
                       nextToken)) { // incomplete bracket
                cerr << "Syntax error on line " << nextToken.lineNum()
                     << ": Incomplete bracket." << endl;
                exit(12);
            }
            addToCST(createNodePtr((nextToken)),
                     RightSibling); // add right bracket

            nextToken = peekToken();
            if (match(Token::Type::Comma, nextToken)) {
                addToCST(createNodePtr((getToken())), RightSibling); // add comma
                currToken = getToken();
                nextToken = getToken();
            } else {

                foundEnd = true;
            }
        } else{
            current -= 2;
            foundEnd = true;
        }
    }
}

void Parser::parseIDENTIFIER_LIST() {
    Token currToken = getToken();
    Token nextToken = getToken();

    bool foundEnd = false;

    while (match(Token::Type::Identifier, currToken) && !foundEnd) {
        if (isReserved(currToken.value())) {
            cerr << "Syntax error on line " << currToken.lineNum()
                 << ": reserved word \"" << currToken.value()
                 << "\" cannot be used for a variable name." << endl;
            exit(1);
        }

        // next token not bracket
        if (!match(Token::Type::LBracket, nextToken)) {
            addToCST(createNodePtr((currToken)),
                     RightSibling); // add variable name
            if (match(Token::Type::Comma, nextToken)) {
                addToCST(createNodePtr((nextToken)), RightSibling); // add comma
                currToken = getToken();
                nextToken = getToken();
            } else {
                foundEnd = true;
                current--;
            }
        } else {
            current -= 2;
            foundEnd = true;
        }
    }
}

void Parser::parseBlockStatement() {
    Token currToken = peekToken();
    if (!match(Token::Type::LBrace, currToken)) {
        cerr << "Syntax error on line " << currToken.lineNum()
             << ": expected '{'" << endl;
        exit(1);
    }

    addToCST(createNodePtr(getToken()), LeftChild);

    parseCompoundStatement(); // add statements

    currToken = peekToken();
    if (!match(Token::Type::RBrace, currToken)) {
        cerr << "Syntax error on line " << currToken.lineNum()
             << ": expected '}'" << endl;
        exit(1);
    }

    addToCST(createNodePtr(getToken()), LeftChild);
}

void Parser::parseProcedure() {
    addToCST(createNodePtr(getToken()), LeftChild); // add 'procedure' identifier to CST
    Token identifier = getToken();
    if (identifier.type() != Token::Type::Identifier) {
        cerr << "Syntax error: Expected an identifier for the "
                "procedure name, found '"
             << identifier.value() << "' at line " << identifier.lineNum()
             << "." << endl;
        exit(13);
    }
    // Create a procedure declaration node with identifier and add to CST
    addToCST(createNodePtr(identifier), LeftChild);

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
    addToCST(lBraceNode, RightSibling);

    // Parse the procedure body (a compound statement).
    parseCompoundStatement();

    NodePtr rBraceNode =
            expectToken(Token::Type::RBrace, "Expected '}' to end the procedure.");
    addToCST(rBraceNode, RightSibling);
}


void Parser::parseFunction() {
    addToCST(createNodePtr(getToken()), LeftChild); // add 'function' identifier to CST
    Token return_type = getToken();

    if (!isDataType(return_type.value())) {
        cerr << "Syntax error: Expected an return type for the "
                "function name, found '"
             << return_type.value() << "' at line " << return_type.lineNum()
             << "." << endl;
        exit(10);
    }
    addToCST(createNodePtr(return_type),RightSibling);
    Token identifier = getToken();
    if (identifier.type() != Token::Type::Identifier) {
        cerr << "Syntax error: Expected an identifier for the "
                "function name, found '"
             << identifier.value() << "' at line " << identifier.lineNum()
             << "." << endl;
        exit(20);
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
            cerr << "Syntax error on line " << dataTypeToken.lineNum()
                 << ": expected a data type specifier, found '" << dataTypeToken.value() << "'" << endl;
            exit(1);
        }
        addToCST(createNodePtr(dataTypeToken), RightSibling);

        // Expect an identifier after data type
        Token identifierToken = getToken();
        if (identifierToken.type() != Token::Type::Identifier) {
            cerr << "Syntax error on line " << identifierToken.lineNum()
                 << ": expected an identifier, found '" << identifierToken.value() << "'" << endl;
            exit(1);
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
            if (arraySizeToken.type() != Token::Type::WholeNumber) {
                cerr << "Syntax error on line " << arraySizeToken.lineNum()
                     << ": expected an array size, found '" << arraySizeToken.value() << "'" << endl;
                exit(6);
            }
            addToCST(createNodePtr(arraySizeToken), RightSibling);

            // Expect and consume ']'
            Token closeBracketToken = getToken();
            if (closeBracketToken.type() != Token::Type::RBracket) {
                cerr << "Syntax error on line " << closeBracketToken.lineNum()
                     << ": expected ']', found '" << closeBracketToken.value() << "'" << endl;
                exit(6);
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
            getToken(); // This consumes the comma token, moving to the next parameter
            addToCST(createNodePtr(nextToken), RightSibling);
        } else {
            cerr << "Syntax error on line " << nextToken.lineNum()
                 << ": expected ',' or ')', found '" << nextToken.value() << "'" << endl;
            exit(6);
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
        cerr << "Syntax error on line " << next.lineNum()<<" token found "<< next.typeToString(next.type())
             << ": expected a statement" << endl;
        exit(4);
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
            cerr << "Syntax error on line " << next.lineNum()
                 << ": unexpected statement error" << endl;
            exit(3);
        }

    }
        // only possible statement that starts with unreserved word
    else {
        parseAssignmentStatement();
    }
}

void Parser::parseSelectionStatement() {
//    NodePtr ifNode = expectToken(Token::Type::Identifier, "Expected 'if'");
        Token ifToken = getToken();
        if(ifToken.value() != "if"){
            cerr<<"Expected an if but got "<<ifToken.value()<<" at line "<< ifToken.lineNum()<<endl;
            exit(37);
        }
             addToCST(createNodePtr(ifToken), LeftChild);

    NodePtr LParenNode = expectToken(Token::Type::LParen, "Expected ')' after boolean expression");
    addToCST(LParenNode, RightSibling);
    // Parse the boolean expression within the if statement.
    parseExpression(); 

    // After the boolean expression, expect a right parenthesis ')'.
    NodePtr RParenNode = expectToken(Token::Type::RParen, "Expected ')' after boolean expression");
    addToCST(RParenNode, RightSibling);

    // The statement or block statement that follows.
    parseStatementOrBlock(); // A helper function that decides whether it's a simple statement or a block statement.

    // Check for "else" 
    Token next = peekToken();
    if (match(Token::Type::Else, next)) {
        // Consume the "else" token.
        NodePtr elseNode = createNodePtr(getToken());
        addToCST(elseNode, RightSibling);

        // Parse the statement or block statement following "else".
        parseStatementOrBlock(); // Reuse the helper function for the "else" part.
    }
}

void Parser::parseStatementOrBlock() {
    // Peek at the next token to decide between a simple statement and a block statement.
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

    } else if (!isReserved(currToken.value()) || currToken.type() == Token::Type::DoubleQuotedString ||currToken.type() == Token::Type::SingleQuotedString) { // If the token is an operand and it's not reserved
        addToCST(createNodePtr(currToken), RightSibling);
        getToken();

        Token nextToken = peekToken();
        if (match(Token::Type::LParen, nextToken) && currToken.type() == Token::Type::Identifier) {
            getToken();
            addToCST(createNodePtr(nextToken), RightSibling);

            if (peekAhead(1).type() == Token::Type::Comma) {
                // If the next token indicates a parameter list
                parseIDENTIFIER_AND_IDENTIFIER_ARRAY_LIST();
            } else {
                // Otherwise, it's an expression within parentheses
                parseExpression();
            }
            NodePtr closingRParen = expectToken(Token::Type::RParen, "Expected ')'");
            addToCST(closingRParen, RightSibling);
        }

        // Check for an operator after the operand
        if (isOperator(peekToken())) {
            Token operatorToken = getToken();
            addToCST(createNodePtr(operatorToken), RightSibling);
            parseExpression();
        }
    } else {
        cerr << "Syntax error: Expected expression, found '" << currToken.value() << "' at line " << currToken.lineNum() << "." << endl;
        exit(1);
    }
}

void Parser::parseAssignmentStatement() {
    Token currtoken = getToken();
    Token next = getToken();

    if(next.type() != Token::Type::AssignmentOperator){
        cerr << "Syntax error: Expected a Assignment opertator, found '"
             << next.value() << "' at line " << next.lineNum() << "."<<endl;
        exit(200);
    }else{
        addToCST(createNodePtr(currtoken),LeftChild);
        addToCST(createNodePtr(next),RightSibling);
    }
    Token token = peekToken();

    if(token.type() == Token::Type::SingleQuotedString ||token.type() == Token::Type::DoubleQuotedString){
        token = getToken();
        addToCST(createNodePtr(token),RightSibling);
    }else if(token.type()== Token::Type::Integer ||
             token.type()== Token::Type::WholeNumber||
             token.type()== Token::Type::HexDigit ||
             token.type()== Token::Type::Digit){
        token = getToken();
        addToCST(createNodePtr(token),RightSibling);

    }
    else{
        parseExpression();
    }

    token = getToken();
    if(token.type() != Token::Type::Semicolon){
        cerr << "Syntax error: Expected a semicolon, found '"
             << token.value() << "' at line " << token.lineNum() << "."<<endl;
        exit(201);
    }
    addToCST(createNodePtr(token),RightSibling);
}     // not done

void Parser::parseInLineStatement() {
    Token next = peekToken();

    if (!match(Token::Type::Identifier, next)) {
        cerr << "Syntax error on line " << next.lineNum()
             << ": unexpected token in inLine statement." << endl;
        exit(1);
    }

    if (isReserved(next.value())) {
        cerr << "Syntax error on line " << next.lineNum()
             << ": can't use reserved word in statements." << endl;
        exit(1);
    }

    // identifier
    addToCST(createNodePtr(getToken()), RightSibling);
    // =
    addToCST(expectToken(Token::Type::AssignmentOperator, "Error expected '='"), RightSibling);
    // expression
    parseExpression();

}

void Parser::parseIterationStatement() {
    Token next = peekToken();

    if (!match(Token::Type::Identifier, next)) {
        cerr << "Syntax error on line " << next.lineNum()
             << ": unexpected token in iterator." << endl;
        exit(1);
    }

    if (next.value() == "for") {
        // for
        addToCST(createNodePtr(getToken()), LeftChild);
        // (
        addToCST(expectToken(Token::Type::LParen, "Syntax error: missing '('"), RightSibling);
        // in line statement
        parseInLineStatement();
        // semicolon
        addToCST(expectToken(Token::Type::Semicolon, "Syntax error: missing ';'"), RightSibling);
        // expression
        parseExpression();
        // semicolon
        addToCST(expectToken(Token::Type::Semicolon, "Syntax error: missing ';'"), RightSibling);
        // in line statement
        parseInLineStatement();
        // )
        addToCST(expectToken(Token::Type::LParen, "Syntax error: missing ')'"), RightSibling);

        next = peekToken();

        // finish with a block statement or a single statement
        if (match(Token::Type::LBracket, next))
            parseBlockStatement();
        else
            parseStatement();


    }
    else if (next.value() == "while") {
        // while
        addToCST(createNodePtr(getToken()), LeftChild);
        // (
        addToCST(expectToken(Token::Type::LParen, "Syntax error: missing '('."), RightSibling);
        // expression
        parseExpression();
        // )
        addToCST(expectToken(Token::Type::LParen, "Syntax error: missing '('."), RightSibling);

        next = peekToken();

        // finish with a block statement or a single statement
        if (match(Token::Type::LBracket, next))
            parseBlockStatement();
        else
            parseStatement();

    }
    else {
        cerr << "Syntax error on line " << next.lineNum()
             << ": unexpected iterator identifier." << endl;
        exit(1);
    }
}

void Parser::parsePrintfStatement() {
    getToken();

    expectToken(Token::Type::LParen, "Expected '(' after 'printf'");

    Token nextToken = peekToken();
    if (!match(Token::Type::DoubleQuotedString, nextToken) && !match(Token::Type::SingleQuotedString, nextToken)) {
        cerr << "Syntax error: Expected a quoted string after 'printf(', found '" << nextToken.value() << "' at line " << nextToken.lineNum() << "." << endl;
        exit(1);
    }
    Token stringToken = getToken();
    addToCST(createNodePtr(stringToken), LeftChild);

    nextToken = peekToken();
    if (match(Token::Type::Comma, nextToken)) {
        addToCST(createNodePtr(getToken()), RightSibling);
        parseIDENTIFIER_AND_IDENTIFIER_ARRAY_LIST();
    }

    expectToken(Token::Type::RParen, "Expected ')' after printf statement");

    expectToken(Token::Type::Semicolon, "Expected ';' at the end of printf statement");
}


void Parser::parseReturnStatement() {
//    NodePtr returnNode = expectToken(Token::Type::Return, "Syntax error: Expected 'return'");
    Token return_token= getToken();

    if(return_token.value() != "return"){
        cerr<<"Expected an return "<<return_token.value()<<" at line "<< return_token.lineNum()<<endl;
        exit(23);
    }
    addToCST(createNodePtr(return_token), LeftChild);

    // NOTE: Currenlty not worrying about returning anything other than an Identifier
    // Peek at the next token to decide if an Identifier follows
     Token nextToken = peekToken();
//    if (match(Token::Type::Identifier, nextToken)) {
//        addToCST(createNodePtr(nextToken), RightSibling); // Adjust as necessary for your tree structure
//    }
        if(peekToken().type() == Token::Type::SingleQuotedString ||
                peekToken().type() == Token::Type::DoubleQuotedString){
            addToCST(createNodePtr(getToken()),RightSibling);
        }else{parseExpression();}

    // Regardless of whether an Identifier was found, a semicolon is expected next
//    NodePtr semicolonNode = expectToken(Token::Type::Semicolon, "Syntax error: Expected ';' after return statement");
    Token semiToken = getToken();
    if(semiToken.type() != Token::Type::Semicolon){
        cerr<<"Expected an ; but got "<<semiToken.value()<<" at line "<< semiToken.lineNum()<<endl;
        exit(39);
    }
    addToCST(createNodePtr(semiToken), RightSibling); // Adjust insertion mode as needed
}

// A helper method to consume the next token and validate its type
// Also add the expected token to the CST if it matches.
NodePtr Parser::expectToken(Token::Type expectedType,
                            const std::string &errorMessage) {
    Token t = getToken();
    if (t.type() != expectedType) {
        cerr << errorMessage << " Found '" << Token::typeToString(t.type())
             << "' at line " << t.lineNum() << "." << endl;
        exit(17);
    }
    // Create a NodePtr from the token and return it
    return createNodePtr(t);
}

// A helper method to peek at the current token without incrementing
// 'current'
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
        throw std::runtime_error("Unexpected end of input while peeking at token.");
    }
    return tokens[current + offset];
}


bool isDataType(string id) {
    if (id == "char" || id == "int" || id == " bool")
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
    if (t.type() == Token::Type::Plus
        || t.type() == Token::Type::Minus
        || t.type() == Token::Type::Slash
        || t.type() == Token::Type::Asterisk
        || t.type() == Token::Type::Modulo
        || t.type() == Token::Type::Caret
        || t.type() == Token::Type::Lt
        || t.type() == Token::Type::Gt
        || t.type() == Token::Type::LtEqual
        || t.type() == Token::Type::GtEqual
        || t.type() == Token::Type::BooleanAnd
        || t.type() == Token::Type::BooleanOr
        || t.type() == Token::Type::BooleanNot
        || t.type() == Token::Type::BooleanEqual
        || t.type() == Token::Type::BooleanNotEqual
            )
        return true;
    return false;
}