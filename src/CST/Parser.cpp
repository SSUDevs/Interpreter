
#include "Parser.h"
#include <iostream>
using namespace std;
// Use make_shared to dynamically allocate Node instances. 
// When a new node is created, it's managed by a shared_ptr.

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

NodePtr Parser::parse() {

    while (current < tokens.size()) {

        Token t = getToken();

        if (t.type() == Token::Type::Identifier) {
            string tokenValue = t.value();

            if (isDataType(tokenValue)) {
                parseDeclaration();
            }   
            else if (tokenValue == "procedure") {
                parseProcedure();
            }  
            else if (tokenValue == "function") {
                // parseFunction();
            }
            else { // error, global scope can only contain global variable declarations, procedures, and functions
                cerr << "Invalid syntax in global scope at line " << t.lineNum() << endl;
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

NodePtr Parser::createNodePtr(const Token& token) {
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



    if (match(Token::Type::Identifier, currToken) && isDataType(currToken.value())) {
        addToCST(createNodePtr(currToken),
                 LeftChild); // add data type id to CST

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

    while (!match(Token::Type::Semicolon, tokens[current])){
        parseIDENTIFIER_ARRAY_LIST();
        parseIDENTIFIER_LIST();
    }
}

void Parser::parseIDENTIFIER_ARRAY_LIST() {
    Token currToken = getToken();
    Token nextToken = getToken();
    bool foundEnd = false;

    while (match(Token::Type::Identifier, currToken) && !foundEnd) {
        if (isReserved(currToken.value())) {    // check reserved
            cerr << "Syntax error on line " << currToken.lineNum() << ": reserved word \""
                 << currToken.value() << "\" cannot be used for a variable name." << endl;
            exit(1);
        }

        if (match(Token::Type::LBracket, nextToken)){
            addToCST(createNodePtr((currToken)), RightSibling); // add array name
            addToCST(createNodePtr((nextToken)), RightSibling); // add left bracket

            Token num = getToken();
            if (isReserved(num.value())) {    // check reserved
                cerr << "Syntax error on line " << num.lineNum() << ": reserved word \""
                     << num.value() << "\" cannot be used for a variable name." << endl;
                exit(1);
            }
            if (stoi(num.value()) <= 0 && !match(Token::Type::Identifier, num)) {     // ERROR negative array size
                cerr << "Syntax error on line " << num.lineNum() << ": array declaration size must be a positive integer." << endl;
                exit(1);
            }
            addToCST(createNodePtr((num)), RightSibling); // add num/variable name

            nextToken = getToken(); // get right bracket
            if (!match(Token::Type::RBracket, nextToken)) {     // ERROR negative array size
                cerr << "Syntax error on line " << nextToken.lineNum() << ": Incomplete bracket." << endl;
                exit(1);
            }
            addToCST(createNodePtr((nextToken)), RightSibling); // add right bracket

            nextToken = getToken();
            if (match(Token::Type::Comma, nextToken)) {
                addToCST(createNodePtr((nextToken)), RightSibling); // add comma
                currToken = getToken();
                nextToken = getToken();
            } else {
                foundEnd = true;
                current--;
            }
        }
        else
            current-=2;
    }


}

void Parser::parseIDENTIFIER_LIST() {
    Token currToken = getToken();
    Token nextToken = getToken();

    bool foundEnd = false;

    while (match(Token::Type::Identifier, currToken) && !foundEnd) {
        if (isReserved(currToken.value())) {
            cerr << "Syntax error on line " << currToken.lineNum() << ": reserved word \""
                 << currToken.value() << "\" cannot be used for a variable name." << endl;
            exit(1);
        }

        // next token not bracket
        if (!match(Token::Type::LBracket, nextToken)) {
            addToCST(createNodePtr((currToken)), RightSibling); // add variable name
            if (match(Token::Type::Comma, nextToken)) {
                addToCST(createNodePtr((nextToken)), RightSibling); // add comma
                currToken = getToken();
                nextToken = getToken();
            } else {
                foundEnd = true;
                current--;
            }
        }
        else
            current-=2;
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
    Token next = getToken();

    NodePtr parameterListNode;
    if (next.value() == "void") {
        // If 'void', create a void node for the parameter list
        parameterListNode =
            std::make_shared<Node>(Token(Token::Type::Void, "void"));
    } else {
        // If the next token is not 'void', put it back to process in
        // parseParameterList
        current--;
        // Parse the parameter list
        parameterListNode = parseParameterList();
    }
    // Attach the returned parameter list node to the procedure node
    procedureNode->addLeftChild(parameterListNode);

    // Expect a right parenthesis ')' ending the parameter list
    expectToken(Token::Type::RParen, "Expected ')' after parameter list.");
    // Expect a left brace '{' starting the procedure body
    expectToken(Token::Type::LBrace,
                "Expected '{' to start the procedure body.");


    // NEED TO BE IMPLEMENTED

    // Parse the compound statement that is the procedure body
    // NodePtr compoundStatementNode = parseCompoundStatement();

    // // Attach the compound statement to the procedure node
    // procedureNode->addRightSibling(compoundStatementNode);

    // Finally, expect a right brace '}' to end the procedure
    expectToken(Token::Type::RBrace, "Expected '}' to end the procedure.");

    // Add the procedure node to the CST containing the body as well attached to
    addToCST(procedureNode, LeftChild);
}

NodePtr Parser::parseParameterList() {
    // Create a node to represent the parameter list in the CST
    NodePtr parameterListNode = std::make_shared<Node>(
        Token(Token::Type::ParameterList, "ParameterList"));

    // Parse the parameter list which is not 'void'
    // Loop until a ')' token is encountered which indicates the end
    while (true) {
        Token nextToken = getToken();
        if (nextToken.type() == Token::Type::RParen) {
            current--; // Put back the ')' token for proper handling in the
                       // calling function
            break;
        }

        if (!isDataType(nextToken.value())) {
            cerr << "Expected a data type in parameter list, found '" << nextToken.value() << "' at line " << nextToken.lineNum() << "." << endl;
            exit(1);
        }

        Token paramName = getToken();
        if (paramName.type() != Token::Type::Identifier) {
            cerr << "Expected an identifier for parameter name, found '"
                 << paramName.value() << "' at line " << paramName.lineNum()
                 << "." << endl;
            exit(1);
        }

        // Create nodes for the datatype and parameter name
        NodePtr typeNode = createNodePtr(nextToken);
        NodePtr nameNode = createNodePtr(paramName);
        typeNode->addLeftChild(nameNode); // Link the identifier as the left
                                          // child of the datatype node

        // Link the current parameter node as a sibling of the previous

        // Find the last parameter node added
        NodePtr lastParam = parameterListNode->leftChild();
        while (lastParam->getRightSibling()) {
            lastParam = lastParam->getRightSibling();
        }
        lastParam->addRightSibling(typeNode);

        // If the next token is a comma, consume it and move on to the next
        // parameter
        Token t = getToken();
        if (t.type() == Token::Type::Comma) {
            getToken(); // Get rid of the comma token
        }
    }

    // Once all parameters are processed or if it was 'void', then need to
    // attach the parameter list node to the function/procedure node
    lastNode->addLeftChild(parameterListNode);
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

// A helper method to peek at the current token without incrementing 'current'
Token Parser::peekToken() const {
    if (current < tokens.size()) {
        return tokens[current]; 
    } else {
        throw std::runtime_error("Unexpected end of input while peeking at token.");
    }
}

// NOT YET IMPLEMENTED FOR NOW
// NodePtr Parser::parseCompoundStatement() {
//     // Placeholder 
// }

void Parser::parseExpression() { }

void Parser::parseSelectionStatement() {
    // Used for parsing selection statements (if-else)
}

void Parser::parseNumericalExpression() {
}

void Parser::parseBooleanExpression() {
}


bool isDataType(string id) {
    if (id == "char" || id == "int" || id == " bool")
        return true;
    return false;
}


bool isReserved(string id) {
    if (id == "char" || id == "int" || id == "bool" 
        || id == "void" || id =="function" || id == "procedure" || id == "main"
        || id == "return" || id == "printf" || id == "getchar" 
        || id == "if" || id == "else" || id == "for" || id == "while"
        || id == "TRUE" || id == "FALSE")
        return true;
    return false;
}
