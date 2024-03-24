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
                pasrseFunction();
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

void Parser::parseProcedure() {

}

void Parser::pasrseFunction() {

}

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