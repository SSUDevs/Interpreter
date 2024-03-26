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
            exit(1);
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
                exit(1);
            }
            if (stoi(num.value()) <= 0 &&
                !match(Token::Type::Identifier,
                       num)) { // ERROR negative array size
                cerr << "Syntax error on line " << num.lineNum()
                     << ": array declaration size must be a positive integer."
                     << endl;
                exit(1);
            }
            addToCST(createNodePtr((num)),
                     RightSibling); // add num/variable name

            nextToken = getToken(); // get right bracket
            if (!match(Token::Type::RBracket,
                       nextToken)) { // ERROR negative array size
                cerr << "Syntax error on line " << nextToken.lineNum()
                     << ": Incomplete bracket." << endl;
                exit(1);
            }
            addToCST(createNodePtr((nextToken)),
                     RightSibling); // add right bracket

            nextToken = getToken();
            if (match(Token::Type::Comma, nextToken)) {
                addToCST(createNodePtr((nextToken)), RightSibling); // add comma
                currToken = getToken();
                nextToken = getToken();
            } else {
                foundEnd = true;
                current--;
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
        exit(1);
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
    cout << "current return type " << return_type.value() << endl;
    if (!isDataType(return_type.value())) {
        cerr << "Syntax error: Expected an return type for the "
                "function name, found '"
             << return_type.value() << "' at line " << return_type.lineNum()
             << "." << endl;
        exit(10);
    }
    Token identifier = getToken();
    if (identifier.type() != Token::Type::Identifier) {
        cerr << "Syntax error: Expected an identifier for the "
                "function name, found '"
             << identifier.value() << "' at line " << identifier.lineNum()
             << "." << endl;
        exit(20);
    }
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
        cerr << "Syntax error on line " << next.lineNum()
             << ": expected a statement" << endl;
        exit(1);
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
            exit(1);
        }

    }
    // only possible statement that starts with unreserved word
    else {
        parseAssignmentStatement();
    }
}

void Parser::parseExpression() {
    Token nextToken = peekToken();
    if (isBooleanOperator(nextToken.type()) ||
        isBooleanValue(nextToken.value())) {
        parseBooleanExpression();
    } else {
        parseNumericalExpression();
    }
}

void Parser::parseSelectionStatement() {
    // Used for parsing selection statements (if-else)
}

void Parser::parseNumericalExpression() {
    Token currToken = peekToken();
    if (match(Token::Type::LParen, currToken)) {
        getToken(); // consume '('
        parseNumericalExpression();
        expectToken(Token::Type::RParen, "Expected ')'");
    } else {
        parseNumericalOperand();

        Token nextToken = peekToken();
        if (isNumericalOperator(nextToken.type())) {
            getToken(); // Consume the operator
            addToCST(createNodePtr(nextToken), RightSibling);

            parseNumericalExpression();
        }
    }
}

void Parser::parseNumericalOperand() {
    Token currToken = getToken();
    if (!match(Token::Type::Identifier, currToken) &&
        !match(Token::Type::WholeNumber, currToken) &&
        !match(Token::Type::Integer, currToken) &&
        !match(Token::Type::Digit, currToken) &&
        !match(Token::Type::HexDigit, currToken)) {
        cerr << "Syntax error: Expected a numerical operand, found '"
             << currToken.value() << "' at line " << currToken.lineNum() << "."
             << endl;
        exit(1);
    }
    addToCST(createNodePtr(currToken), RightSibling);
}

void Parser::parseAssignmentStatement() {}     // not done
void Parser::parseIterationStatement() {}     // not done
void Parser::parsePrintfStatement() {}        // not done

void Parser::parseBooleanExpression() {
    Token currToken = peekToken();

    if (/*match(Token::Type::BooleanTrue, currToken) ||
           match(Token::Type::BooleanFalse, currToken) ||*/
        match(Token::Type::Identifier, currToken)) {
        getToken();
        addToCST(createNodePtr(currToken), RightSibling);

        Token nextToken = peekToken();

        if (isBooleanOperator(nextToken.type())) {
            getToken();
            addToCST(createNodePtr(nextToken), RightSibling);

            parseBooleanExpression();
        }
    } else if (match(Token::Type::LParen, currToken)) {
        getToken();
        parseBooleanExpression();
        expectToken(Token::Type::RParen, "Expected ')'");
    } else {
        parseNumericalExpression();

        Token opToken = getToken();
        if (!isComparisonOperator(opToken.type())) {
            cerr << "Syntax error: Expected a comparison operator, found '"
                 << opToken.value() << "' at line " << opToken.lineNum() << "."
                 << endl;
            exit(1);
        }
        addToCST(createNodePtr(opToken), RightSibling);

        parseNumericalExpression();
    }
}

void Parser::parseReturnStatement() {
    NodePtr returnNode = expectToken(Token::Type::Return, "Syntax error: Expected 'return'");
    addToCST(returnNode, LeftChild); 

    // NOTE: Currenlty not worrying about returning anything otherthan an Identifier
    // Peek at the next token to decide if an Identifier follows
    Token nextToken = peekToken();
    if (match(Token::Type::Identifier, nextToken)) {
        addToCST(createNodePtr(nextToken), RightSibling); // Adjust as necessary for your tree structure
    }

    // Regardless of whether an Identifier was found, a semicolon is expected next
    NodePtr semicolonNode = expectToken(Token::Type::Semicolon, "Syntax error: Expected ';' after return statement");
    addToCST(semicolonNode, RightSibling); // Adjust insertion mode as needed
}

// A helper method to consume the next token and validate its type
// Also add the expected token to the CST if it matches.
NodePtr Parser::expectToken(Token::Type expectedType,
                            const std::string &errorMessage) {
    Token t = getToken();
    if (t.type() != expectedType) {
        cerr << errorMessage << " Found '" << Token::typeToString(t.type())
             << "' at line " << t.lineNum() << "." << endl;
        exit(1);
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

bool Parser::isBooleanOperator(Token::Type type) {
    return type == Token::Type::BooleanAnd || type == Token::Type::BooleanOr ||
           type == Token::Type::BooleanNot ||
           type == Token::Type::BooleanEqual ||
           type == Token::Type::BooleanNotEqual;
}

bool Parser::isBooleanValue(const std::string &value) {
    return value == "true" || value == "false";
}

bool Parser::isNumericalOperator(Token::Type type) {
    return type == Token::Type::Plus || type == Token::Type::Minus ||
           type == Token::Type::Asterisk || type == Token::Type::Slash ||
           type == Token::Type::Modulo;
}

bool Parser::isComparisonOperator(Token::Type type) {
    return type == Token::Type::Lt || type == Token::Type::Gt ||
           type == Token::Type::LtEqual || type == Token::Type::GtEqual ||
           type == Token::Type::BooleanEqual ||
           type == Token::Type::BooleanNotEqual;
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
